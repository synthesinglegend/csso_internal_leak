#pragma once
template <typename Return, typename ... Arguments>
constexpr Return Call(void* vmt, const std::uint32_t index, Arguments ... args) noexcept
{
	using Function = Return(__thiscall*)(void*, decltype(args)...);
	return (*static_cast<Function**>(vmt))[index](vmt, args...);
}

template< typename T >
T vfunc(void* vTable, int iIndex)
{
	return (*(T**)vTable)[iIndex];
}

template<typename FuncType>
__forceinline static FuncType call_virtual(void* ppClass, int index) {
	int* pVTable = *(int**)ppClass;
	int dwAddress = pVTable[index];
	return (FuncType)(dwAddress);
}

template < size_t index, typename ret, class ... args_ >
constexpr __forceinline ret get_vfunc(void* thisptr, args_... args) {
	using fn = ret(__thiscall*)(void*, args_...);

	auto fn_ptr = (fn)(*(uintptr_t**)thisptr)[index];
	return fn_ptr(thisptr, args...);
}

