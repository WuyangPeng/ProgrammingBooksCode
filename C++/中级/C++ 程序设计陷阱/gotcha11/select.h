#ifndef SELECT_H
#define SELECT_H

//
//	Borrowed from Andrei Alexandrescu's Loki library.
//

template <bool, typename A, typename>
struct Select {
    typedef A Result;
};

template <typename A, typename B>
struct Select<false, A, B> {
    typedef B Result;
};

#endif
