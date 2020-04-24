// Library export macro
#ifdef _WIN32

#if defined(MICROENGINE_EXPORTS)

#define ENGINE_API extern "C" __declspec(dllexport)
#define ENGINE_CLASS __declspec(dllexport)

#elif defined(MICROENGINE_LOADDLL)

#define ENGINE_API extern "C" __declspec(dllimport)
#define ENGINE_CLASS __declspec(dllimport)

#else  // defined(MICROENGINE_EXPORTS)

#define ENGINE_API extern "C"
#define ENGINE_CLASS __declspec(dllexport)

#endif  // defined(MICROENGINE_EXPORTS)

#else  // _WIN32

#define ENGINE_API
#define ENGINE_CLASS

#endif  // _WIN32