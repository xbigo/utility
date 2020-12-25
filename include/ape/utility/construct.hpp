#ifndef APE_UTILITY_CONSTRUCT_H
#define APE_UTILITY_CONSTRUCT_H
#include <ape/config.hpp>

#include <memory>   // for std::addressof
#include <utility> // for std::forward

BEGIN_APE_NAMESPACE

template<typename T> inline constexpr
void default_construct(T& t)
    noexcept(std::is_nothrow_default_constructible_v<T>)
{
    new (std::addressof(t)) T();
}
template<typename T> inline constexpr
void default_construct_uninit(T& t)
    noexcept(std::is_nothrow_default_constructible_v<T>)
{
    new (std::addressof(t)) T;
}

template<typename T, typename ...U> inline constexpr
void emplace_construct(T& t, U&& ... args)
    noexcept(std::is_nothrow_constructible_v<T, U&&...>){
    new (std::addressof(t)) T(std::forward<U>(args)...);
}

template<typename T> inline constexpr
void destruct(T& t) noexcept{
    t.~T();
}

template<typename ForwardItr> inline constexpr
void destruct(ForwardItr first, ForwardItr last) noexcept{
    for(; first != last; ++first) destruct(*first);
}

template<typename ForwardItr> inline constexpr
void destruct(ForwardItr first, ForwardItr last) noexcept{
    for(; first != last; ++first) destruct(*first);
}

#if (CPP_STANDARD >= CPP_STD_20)
template<std::ranges::input_range R> inline constexpr
void destruct(R& r) noexcept {
	for(auto&& v) destruct(v);
}

#endif

END_APE_NAMESPACE

#endif //end APE_UTILITY_CONSTRUCT_H

