#pragma once
void Log(const char* message)
{
#ifdef DEBUG

	printf("[INFO] - %s\n", message);

#endif
}