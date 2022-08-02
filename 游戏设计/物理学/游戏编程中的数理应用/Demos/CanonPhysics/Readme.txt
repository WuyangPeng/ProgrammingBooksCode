Bugs:

This project will not compile in MSVC++ 6.0 (SP5).  It refuses to allow private destructors.  The workaround would be to make them public.

Or e-mail me (mfawcett@fullsail.com) with a better solution.

The Singleton pattern used is obviously flawed in many ways, but the alternatives would overly complicate the subject matter.
