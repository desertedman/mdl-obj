# Notes

My notes on TinyObjLoader's internal workings

## TinyObjLoader

- Provide `TINYOBJLOADER_IMPLEMENTATION` define to load implementation
- Uses `StreamReader` under the hood to read `ifstream`s (line 5916)

### StreamReader class

#### Constructor

- Explicit constructor gets start & end position of stream
- Does a lot of casts to record remaining size, especially to see if file size is within bounds & to determine internal buffer length
- Extracts `ifstream` buffer into its own internal buffer (`std::vector<char> owned_buf_`) (line 5965)
- `const char* buf_` points into a character, owned by `owned_buf_`

### LoadObj function

- Wrapper around `LoadObjInternal` function

#### Face Parsing

- Constructs a `face_t` struct, which owns a `std::vector<vertex_index_t> vertex_indices`
- `vertex_index_t` is a wrapper around 3 ints: vertex index, vertex texture coordinate index, and vertex normal index
- Calls `sr_parseTriple` (line 7358), handles various `f` (face) obj formattings
