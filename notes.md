# Notes

My notes on TinyObjLoader's internal workings, particularly its `StreamReader` class

## TinyObjLoader

- Provide `TINYOBJLOADER_IMPLEMENTATION` define to load implementation
- Uses `StreamReader` under the hood to read `ifstream`s (line 5916)

### Constructor

- Explicit constructor gets start & end position of stream
- Does a lot of casts to record remaining size, especially to see if file size is within bounds & to determine internal buffer length
- Extracts `ifstream` buffer into its own internal buffer (`std::vector<char> owned_buf_`) (line 5965)
- `const char* buf_` points into a character, owned by `owned_buf_`
