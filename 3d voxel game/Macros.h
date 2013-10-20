#pragma once

#ifdef _SERVER
#define SERVER(...) __VA_ARGS__
#define CLIENT(VOID)
#else
#define SERVER(VOID)
#define CLIENT(...) __VA_ARGS__
#endif

