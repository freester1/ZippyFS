#ifndef BLOCK_CACHE_H
#define BLOCK_CACHE_H

#include <mutex>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <cstdint>
#include <cassert>
#include "block.h"
#include "fuse_ops.h"
//#include "inode.h"
/**
 * represents an in-memory Block Cache
 * @author Arvin Sharma
 */
class BlockCache {
  public:
    /**
     * constructs a BlockCache that flushes to the given dir
     * @param path_to_shdw is the path of the shadow dir
     */
    BlockCache(std::string path_to_shdw);

    /**
     * writes to the given file in cache
     * @return number of bytes written
     */
    int write(std::string path, const uint8_t* buf, uint64_t size, uint64_t offset);

    /**
     * reads from the given file in cache
     * @return the number of bytes read
     */
    int read(std::string path, uint8_t* buf, uint64_t size, uint64_t offset);

    /**
     * determines if the thing in path is in cache
     * @param true if the file exists, false otherwise
     */
    bool in_cache(std::string path);

    /**
     * flushes the contents of this block cache to
     * the shadow directory.
     * Also flushes cache_data_ to an index file in the directory
     * @return 0 for success, nonzero otherwise
     */
    int flush_to_shdw();

    /** loads the thing to this cache */
    int load_to_cache(std::string path);



  private:

    /** absolute path of shadow directory */
    std::string path_to_shdw_;

    /** file cache **/
    std::map<std::string, std::map<uint64_t, std::shared_ptr<Block>>> file_cache_;

    /** for multithreaded mode potentially */
    std::mutex mutex_;

    /** represents entries (path, meta-data) in an index file for files in cache */
    std::map<std::string, std::string> cache_data_;

    /** represents meta data for files in cache */
    // std::map<std::string, std::shared_ptr<Inode>> meta_data_;

};
#endif
