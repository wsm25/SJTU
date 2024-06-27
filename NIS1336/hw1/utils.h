#ifdef __cplusplus
extern "C"{
#endif
/// @brief parse argument "-h" and "-u" only
/// @param argc argument count
/// @param argv argument vector
/// @param help help string
/// @return 0 if continue, non-0 if exit
int parse_arg(const int argc, char* argv[], const char* help);

/// @brief convert string to unsigned integer from 0-16,777,216, with check of
///        invalid char
/// @param s string to be converted
/// @return integer. -1 if error is detected
int atoi(const char* s);
#ifdef __cplusplus
}
#endif