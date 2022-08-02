//+---------------------------------------------------------------+
// BlockingNotifySyncCtx.cs
// Chapter 16, page 851
//
// A synchronization context that notifies upon blocking.
//
// (c) 2007-2009, Joe Duffy
//+---------------------------------------------------------------+

using System;
using System.Threading;

namespace CPOW_DotNet.Chap16
{
    public delegate object PreWaitNotification(
        IntPtr[] waitHandles,
        bool waitAll,
        int millisecondsTimeout
    );

    public delegate void PostWaitNotification(
        IntPtr[] waitHandles,
        bool waitAll,
        int millisecondsTimeout,
        int ret,
        Exception ex,
        object state
    );

    public class BlockingNotifySynchronizationContext : SynchronizationContext
    {

        private SynchronizationContext m_captured;
        private PreWaitNotification m_pre;
        private PostWaitNotification m_post;

        public BlockingNotifySynchronizationContext(
            PreWaitNotification pre, PostWaitNotification post) :
            this(SynchronizationContext.Current, pre, post)
        {
        }

        public BlockingNotifySynchronizationContext(
            SynchronizationContext captured,
            PreWaitNotification pre, PostWaitNotification post)
        {
            m_captured = captured;
            m_pre = pre;
            m_post = post;

            // Make sure we get notified of blocking calls.
            SetWaitNotificationRequired();
        }

        public override SynchronizationContext CreateCopy()
        {
            return new BlockingNotifySynchronizationContext(
                m_captured == null ? null : m_captured.CreateCopy(),
                m_pre, m_post);
        }

        public override void Post(SendOrPostCallback cb, object s)
        {
            if (m_captured != null)
                m_captured.Post(cb, s);
            else
                base.Post(cb, s);
        }

        public override void Send(SendOrPostCallback cb, object s)
        {
            if (m_captured != null)
                m_captured.Send(cb, s);
            else
                base.Send(cb, s);
        }

        public override void OperationCompleted()
        {
            if (m_captured != null)
                m_captured.OperationCompleted();
            else
                base.OperationCompleted();
        }

        public override void OperationStarted()
        {
            if (m_captured != null)
                m_captured.OperationStarted();
            else
                base.OperationStarted();
        }

        public override int Wait(
            IntPtr[] waitHandles, bool waitAll, int millisecondsTimeout)
        {
            // Invoke the pre callback.
            object s = m_pre(waitHandles, waitAll, millisecondsTimeout);

            // Now perform the wait.
            int ret = 0;
            Exception ex = null;
            try
            {
                if (m_captured != null)
                    ret = m_captured.Wait(
                        waitHandles, waitAll, millisecondsTimeout);
                else
                    ret = base.Wait(
                        waitHandles, waitAll, millisecondsTimeout);
            }
            catch (Exception e)
            {
                ex = e;
                throw;
            }
            finally
            {
                // Invoke the post callback.
                m_post(
                    waitHandles, waitAll, millisecondsTimeout, ret, ex, s);
            }

            return ret;
        }
    }
}
