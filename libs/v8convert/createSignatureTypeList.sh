#!/bin/bash
########################################################################
# A quick hack to generate Signature templates.

from=${1-0}
to=$2

if [[ 'x' = "x${to}" ]]; then
    to=$from
    from=0
fi

tparam='typename RV'
targs=''

if [[ 0 = $from ]]; then
#template <typename Sig> struct Signature;

cat <<EOF

template <typename RV>
struct Signature< RV () >
{
    typedef RV ReturnType;
    enum { Arity = 0, IsConst = 0 };
    typedef void Context;
    //typedef RV (FunctionType)();
    typedef RV (*FunctionType)();
    typedef tmp::NilType Head;
    typedef Head Tail;
};
template <typename RV>
struct Signature< RV (*)() > : Signature<RV ()>
{};
template <typename RV>
struct Signature< RV () const > : Signature<RV ()>
{
    enum { IsConst = 1 };
};
EOF
from=$((from + 1))
fi
i=$from
while [[ $i -le $to ]]; do
    tparam="${tparam}, typename A${i}"
    if [[ "X" != "X${targs}" ]]; then
        targs="${targs}, A${i}"
    else
        targs="A1"
    fi

    head="${targs%%,*}"
    tail="${targs#*,}"
    if [[ "$tail" = "$head" ]]; then # happens on 1-arity form
        #if [[ $i -eq 0 ]]; then
            tail="tmp::NilType"
        #else
        #    tail="Signature< RV () >"
        #fi
    else
        tail="Signature<RV (${tail})>"
    fi
    
    cat <<EOF
//! Specialization for ${i} arg(s).
template <$tparam>
struct Signature< RV (${targs}) >
{
    typedef RV ReturnType;
    enum { Arity = ${i}, IsConst = 0 };
    typedef void Context;
    typedef RV (*FunctionType)(${targs});
    typedef ${head} Head;
    typedef ${tail} Tail;
};

//! Specialization for ${i} arg(s).
template <$tparam>
struct Signature< RV (${targs}) const > : Signature<RV (${targs})>
{
    enum { IsConst = 1 };
};

//! Specialization for ${i} arg(s).
template <$tparam>
struct Signature< RV (*)(${targs}) > : Signature<RV (${targs})>
{};

//! Specialization for T methods taking ${i} arg(s).
template <typename T, $tparam>
struct Signature< RV (T::*)(${targs}) > : Signature<RV (${targs})>
{
    typedef T Context;
};

//! Specialization for T const methods taking ${i} arg(s).
template <typename T, $tparam>
struct Signature< RV (T::*)(${targs}) const > : Signature<RV (${targs}) const>
{
    typedef T Context;
    enum { IsConst = 1 };
};
EOF
    #echo $tparam
    #echo $targs
    i=$((i + 1))
done

