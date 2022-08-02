//+---------------------------------------------------------------+
// StackProbes.cs
// Chapter 4, page 144, 149
//
// Examples of probing for more stack space.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Runtime.InteropServices;

namespace CPOW_DotNet.Chap04
{
    public static class StackProbes
    {
        /// <summary>
        /// Example on page 144 to probe for a certain number of bytes'
        /// worth of stack space.  Sadly this will crash with an overflow.
        /// </summary>
        /// <param name="bytes">The number of bytes to probe for.</param>
        public unsafe static void ProbeForStackSpace(int bytes)
        {
            byte * bb = stackalloc byte[bytes];
        }

        /// <summary>
        /// Example on page 149 to probe for a certain number of bytes'
        /// worth of stack space, but returns false instead of crashing
        /// if insufficient space remains.
        /// </summary>
        /// <param name="bytes">The number of bytes to probe for.</param>
        public unsafe static bool CheckForSufficientStack(long bytes)
        {
            MEMORY_BASIC_INFORMATION stackInfo = new MEMORY_BASIC_INFORMATION();

            // We subtract one page for our request. VirtualQuery rounds up
            // to the next page. But the stack grows down. If we're on the
            // first page (last page in the VirtualAlloc), we'll be moved to
            // the next page, which is off the stack! Note this doesn't work
            // right for IA64 due to bigger pages.
            IntPtr currentAddr = new IntPtr((uint)&stackInfo - 4096);

            // Query for the current stack allocation information.
            VirtualQuery(currentAddr, ref stackInfo,
                sizeof(MEMORY_BASIC_INFORMATION));

            // If the current address minus the base (remember: the stack
            // grows downward in the address space) is greater than the
            // number of bytes requested plus the reserved space at the end,
            // the request has succeeded.
            return ((uint)currentAddr.ToInt64() - stackInfo.AllocationBase) >
                (bytes + STACK_RESERVED_SPACE);
        }

        // We are conservative here. We assume that the platform needs a
        // whole 16 pages to respond to stack overflow (using an X86/X64
        // page-size, not IA64). That's 64KB, which means that for very
        // small stacks (e.g. 128KB) we'll fail a lot of stack checks
        // incorrectly.
        private const long STACK_RESERVED_SPACE = 4096 * 16;

        [DllImport("kernel32.dll")]
        private static extern int VirtualQuery(
            IntPtr lpAddress,
            ref MEMORY_BASIC_INFORMATION lpBuffer,
            int dwLength);

        private struct MEMORY_BASIC_INFORMATION
        {
            internal uint BaseAddress;
            internal uint AllocationBase;
            internal uint AllocationProtect;
            internal uint RegionSize;
            internal uint State;
            internal uint Protect;
            internal uint Type;
        }
    }
}