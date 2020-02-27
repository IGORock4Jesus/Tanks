#pragma once

#ifdef MATHEMATICS_EXPORTS
#define MATHEMATICS_API __declspec(dllexport)
#else
#define MATHEMATICS_API __declspec(dllimport)
#endif // MATHEMATICS_EXPORTS
