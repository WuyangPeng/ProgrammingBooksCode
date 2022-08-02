//-----------------------------------------------------------------
// ImageFilter.cs (c) 2007 by Charles Petzold for "Beautiful Code"
//-----------------------------------------------------------------
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Reflection;
using System.Reflection.Emit;
using System.Runtime.InteropServices;

class ImageFilter
{
    double[] filter;
    int cxFilter;
    int cyFilter;

    public ImageFilter(int cxFilter, double[] filter)
    {
        this.filter = filter;
        this.cxFilter = cxFilter;
        this.cyFilter = filter.Length / cxFilter;
    }

    public bool ApplyFilter(Bitmap bmp, bool willGenerateCode)
    {
        // Check if bitmap is in a good format
        if (bmp.PixelFormat != PixelFormat.Format24bppRgb &&
            bmp.PixelFormat != PixelFormat.Format32bppArgb &&
            bmp.PixelFormat != PixelFormat.Format32bppPArgb &&
            bmp.PixelFormat != PixelFormat.Format32bppRgb)
        {
            return false;
        }

        // Look the bits
        Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
        BitmapData data = bmp.LockBits(rect, ImageLockMode.ReadOnly, 
                                        bmp.PixelFormat);

        // Copy pixels from bitmap to src array
        int cBytes = data.Stride * data.Height;
        byte[] src = new byte[cBytes];
        Marshal.Copy(data.Scan0, src, 0, cBytes);
        bmp.UnlockBits(data);

        // Allocate destination array
        byte[] dst = new byte[cBytes];

        // Execute a filter method
        if (!willGenerateCode)
            FilterMethodOne(src, dst, Math.Abs(data.Stride), Math.Abs(data.Stride) / data.Width);
        else
            FilterMethodTwo(src, dst, Math.Abs(data.Stride), Math.Abs(data.Stride) / data.Width);

        // Copy pixels from dst aray to bitmap
        data = bmp.LockBits(rect, ImageLockMode.WriteOnly, bmp.PixelFormat);
        Marshal.Copy(dst, 0, data.Scan0, cBytes);
        bmp.UnlockBits(data);

        return true;
    }

    // Straight C# approach
    void FilterMethodOne(byte[] src, byte[] dst, int stride, int bytesPerPixel)
    {
        int cBytes = src.Length;
        int cFilter = filter.Length;

        for (int iDst = 0; iDst < cBytes; iDst++)
        {
            double pixelsAccum = 0;
            double filterAccum = 0;

            for (int iFilter = 0; iFilter < cFilter; iFilter++)
            {
                int yFilter = iFilter / cyFilter;
                int xFilter = iFilter % cxFilter;

                int iSrc = iDst + stride * (yFilter - cyFilter / 2) + 
                                    bytesPerPixel * (xFilter - cxFilter / 2);

                if (iSrc >= 0 && iSrc < cBytes)
                {
                    pixelsAccum += filter[iFilter] * src[iSrc];
                    filterAccum += filter[iFilter];
                }
            }

            if (filterAccum != 0)
                pixelsAccum /= filterAccum;

            dst[iDst] = pixelsAccum < 0 ? (byte)0 : (pixelsAccum > 255 ? 
                                            (byte)255 : (byte)pixelsAccum);
        }
    }

    // Generates on-the-fly Intermediate Language
    void FilterMethodTwo(byte[] src, byte[] dst, int stride, int bytesPerPixel)
    {
        int cBytes = src.Length;

        DynamicMethod dynameth = new DynamicMethod("Go", typeof(void),
            new Type[] { typeof(byte[]), typeof(byte[]) }, GetType());

        ILGenerator generator = dynameth.GetILGenerator();

        // Define local variables
        generator.DeclareLocal(typeof(int));        // Index 0 = iDst
        generator.DeclareLocal(typeof(double));     // Index 1 = pixelsAccum
        generator.DeclareLocal(typeof(double));     // Index 2 = filterAccum

        // Set iDst to zero
        generator.Emit(OpCodes.Ldc_I4_0);
        generator.Emit(OpCodes.Stloc_0);

        // Define label at top of iDst loop
        Label labelTop = generator.DefineLabel();
        generator.MarkLabel(labelTop);

        // Set pixelAccum and filterAccum to zero
        generator.Emit(OpCodes.Ldc_R8, 0.0);
        generator.Emit(OpCodes.Dup);
        generator.Emit(OpCodes.Stloc_1);
        generator.Emit(OpCodes.Stloc_2);

        // Loop through the filter array
        for (int iFilter = 0; iFilter < filter.Length; iFilter++)
        {
            // Skip all this logic if the filter element is zero
            if (filter[iFilter] == 0)
                continue;

            int xFilter = iFilter % cxFilter;
            int yFilter = iFilter / cxFilter;
            int offset = stride * (yFilter - cyFilter / 2) +
                        bytesPerPixel * (xFilter - cxFilter / 2);

            // Put src array on stack
            generator.Emit(OpCodes.Ldarg_0);

            // Define labels for branching
            Label labelLessThanZero = generator.DefineLabel();
            Label labelGreaterThan = generator.DefineLabel();
            Label labelLoopBottom = generator.DefineLabel();

            generator.Emit(OpCodes.Ldloc_0);        // dst index on stack
            generator.Emit(OpCodes.Ldc_I4, offset); // offset on stack
            generator.Emit(OpCodes.Add);            // Add the two
            generator.Emit(OpCodes.Dup);            // Duplicate twice
            generator.Emit(OpCodes.Dup);

            // Check if less than zero (pops first index)
            generator.Emit(OpCodes.Ldc_I4_0);
            generator.Emit(OpCodes.Blt_S, labelLessThanZero);

            // Check if greater than size of bitmap (pops second index)
            generator.Emit(OpCodes.Ldc_I4, cBytes);
            generator.Emit(OpCodes.Bge_S, labelGreaterThan);
            
            // Access src array & convert to double
            generator.Emit(OpCodes.Ldelem_U1);
            generator.Emit(OpCodes.Conv_R8);

            // Special processing if filter element is 1
            if (filter[iFilter] == 1)
            {
                // src element is on stack, so do nothing
            }
            else if (filter[iFilter] == -1)
            {
                // Negate src element on stack
                generator.Emit(OpCodes.Neg);
            }
            else
            {
                // Multiply by filter element and accumulate
                generator.Emit(OpCodes.Ldc_R8, filter[iFilter]);
                generator.Emit(OpCodes.Mul);
            }

            // Accumulate pixelsAccum with number on stack
            generator.Emit(OpCodes.Ldloc_1);
            generator.Emit(OpCodes.Add);
            generator.Emit(OpCodes.Stloc_1);

            // Now accumulate filterAccum
            generator.Emit(OpCodes.Ldc_R8, filter[iFilter]);
            generator.Emit(OpCodes.Ldloc_2);    // filterAccum
            generator.Emit(OpCodes.Add);
            generator.Emit(OpCodes.Stloc_2);
            generator.Emit(OpCodes.Br, labelLoopBottom);

            // Clean up at bottom of filter loop
            generator.MarkLabel(labelLessThanZero);
            generator.Emit(OpCodes.Pop);
            generator.MarkLabel(labelGreaterThan);
            generator.Emit(OpCodes.Pop);
            generator.Emit(OpCodes.Pop);
            generator.MarkLabel(labelLoopBottom);
        }

        generator.Emit(OpCodes.Ldarg_1);        // dst array
        generator.Emit(OpCodes.Ldloc_0);        // iDst index

        // Define a couple of labels for branching
        Label labelSkipDivide = generator.DefineLabel();
        Label labelCopyQuotient = generator.DefineLabel();
        Label labelBlack = generator.DefineLabel();
        Label labelWhite = generator.DefineLabel();
        Label labelDone = generator.DefineLabel();

        // Divide pixelsAccum by filterAccum
        generator.Emit(OpCodes.Ldloc_1);        // pixelsAccum
        generator.Emit(OpCodes.Ldloc_2);        // filterAccum
        generator.Emit(OpCodes.Dup);            // Make a copy
        generator.Emit(OpCodes.Ldc_R8, 0.0);    // Put 0 on stack

        // Avoid zero divide
        generator.Emit(OpCodes.Beq_S, labelSkipDivide);
        generator.Emit(OpCodes.Div);            // Divide
        generator.Emit(OpCodes.Br_S, labelCopyQuotient);

        generator.MarkLabel(labelSkipDivide);
        generator.Emit(OpCodes.Pop);            // Pop filterAccum

        generator.MarkLabel(labelCopyQuotient);
        generator.Emit(OpCodes.Dup);            // Make a copy of quotient
        generator.Emit(OpCodes.Dup);            // And another

        // Check if quotient is less than zero
        generator.Emit(OpCodes.Ldc_R8, 0.0);
        generator.Emit(OpCodes.Blt_S, labelBlack);

        // Check if quotient is greater than 255
        generator.Emit(OpCodes.Ldc_R8, 255.0);
        generator.Emit(OpCodes.Bgt_S, labelWhite);

        // Convert value on stack to byte
        generator.Emit(OpCodes.Conv_U1);
        generator.Emit(OpCodes.Br_S, labelDone);

        // If < 0, set it to zero byte
        generator.MarkLabel(labelBlack);
        generator.Emit(OpCodes.Pop);
        generator.Emit(OpCodes.Pop);
        generator.Emit(OpCodes.Ldc_I4_S, 0);
        generator.Emit(OpCodes.Br_S, labelDone);

        // If > 255, set it to 255
        generator.MarkLabel(labelWhite);
        generator.Emit(OpCodes.Pop);
        generator.Emit(OpCodes.Ldc_I4_S, 255);
        
        // At this point, bitmap destination value is on stack
        generator.MarkLabel(labelDone);

        // So just store it in array
        generator.Emit(OpCodes.Stelem_I1);

        // Increment iDst
        generator.Emit(OpCodes.Ldloc_0);    // Put iDst on stack
        generator.Emit(OpCodes.Ldc_I4_1);   // Put 1 on stack
        generator.Emit(OpCodes.Add);        // Add 1 to iDst
        generator.Emit(OpCodes.Dup);        // Duplicate
        generator.Emit(OpCodes.Stloc_0);    // Store result in iDst

        generator.Emit(OpCodes.Ldc_I4, cBytes);  // Put cBytes value on stack
        generator.Emit(OpCodes.Blt, labelTop);   // Go to top if iDst < cBytes

        // All done: Return
        generator.Emit(OpCodes.Ret);

        // Now invoke the method.
        dynameth.Invoke(this, new object[] { src, dst });
    }
}

