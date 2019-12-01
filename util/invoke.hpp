/**
 *  invoke function
 *
 *  The purpose of this header is to benefit from the invoke(x, ...)
 *  syntax without having to include the whole <functional> header.
 *
 */
#pragma once

//* Type aliases
//* Function pointer
template <typename Ret, typename... Args>
using FnPtr = Ret (*)(Args...);

//* Member constant function pointer
template <typename T, typename Ret, typename... Args>
using MemFnptrConst = Ret (T::*)(Args...) const;

//* Member function pointer
template <typename T, typename Ret, typename... Args>
using MemFnptr = Ret (T::*)(Args...);


//* invoke implementation
//* Free function
template <typename Ret, typename... Args>
constexpr Ret invoke(FnPtr<Ret, Args...> fnptr, Args&&... args)
{
    return fnptr(std::forward<Args>(args)...);
}


//* Constant member function, instance as constant pointer
template <typename T, typename Ret, typename... Args>
constexpr Ret invoke(
    MemFnptrConst<T,Ret,Args...>    mem_fnptr,
    T const*                        instance,
    Args&&...                       args
){
    return ((instance)->*(mem_fnptr))(std::forward<Args>(args)...);
}


//* Constant member function, instance as constant reference
template <typename T, typename Ret, typename... Args>
constexpr Ret invoke(
    MemFnptrConst<T,Ret,Args...>    mem_fnptr,
    T const&                        instance,
    Args&&...                       args
){
    return ((instance).*(mem_fnptr))(std::forward<Args>(args)...);
}


//* Member function, instance as mutable pointer
template <typename T, typename Ret, typename... Args>
constexpr Ret invoke(
    MemFnptr<T,Ret,Args...> mem_fnptr,
    T*                      instance,
    Args&&...               args
){
    return ((instance)->*(mem_fnptr))(std::forward<Args>(args)...);
}


//* Member function, instance as mutable reference
template <typename T, typename Ret, typename... Args>
constexpr Ret invoke(
    MemFnptr<T,Ret,Args...> mem_fnptr,
    T&                      instance,
    Args&&...               args
){
    return ((instance).*(mem_fnptr))(std::forward<Args>(args)...);
}
