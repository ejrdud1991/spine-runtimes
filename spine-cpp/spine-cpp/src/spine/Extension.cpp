/******************************************************************************
* Spine Runtimes Software License v2.5
*
* Copyright (c) 2013-2016, Esoteric Software
* All rights reserved.
*
* You are granted a perpetual, non-exclusive, non-sublicensable, and
* non-transferable license to use, install, execute, and perform the Spine
* Runtimes software and derivative works solely for personal or internal
* use. Without the written permission of Esoteric Software (see Section 2 of
* the Spine Software License Agreement), you may not (a) modify, translate,
* adapt, or develop new applications using the Spine Runtimes or otherwise
* create derivative works or improvements of the Spine Runtimes or (b) remove,
* delete, alter, or obscure any trademarks or any copyright, trademark, patent,
* or other intellectual property or proprietary rights notices on or in the
* Software, including any copy thereof. Redistributions in binary or source
* form must include this license and terms.
*
* THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
* USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#include <spine/Extension.h>

#include <fstream>
#include <assert.h>
#include <cstring>

namespace Spine {
    SpineExtension* SpineExtension::_instance = NULL;
    
    void SpineExtension::setInstance(SpineExtension* inValue) {
        assert(!_instance);
        
        _instance = inValue;
    }
    
    SpineExtension* SpineExtension::getInstance() {
        assert(_instance);
        
        return _instance;
    }
    
    SpineExtension::~SpineExtension() {
        // Empty
    }
    
    char* SpineExtension::_readFile(const char* path, int* length) {
        char *data;
        FILE *file = fopen(path, "rb");
        if (!file) return 0;
        
        fseek(file, 0, SEEK_END);
        *length = (int)ftell(file);
        fseek(file, 0, SEEK_SET);
        
        data = SpineExtension::alloc<char>(*length, __FILE__, __LINE__);
        fread(data, 1, *length, file);
        fclose(file);
        
        return data;
    }
    
    SpineExtension::SpineExtension() {
        // Empty
    }
    
    DefaultSpineExtension::~DefaultSpineExtension() {
        // Empty
    }
    
    void* DefaultSpineExtension::_alloc(size_t size, const char* file, int line) {
		if (size == 0)
			return 0;
        void* ptr = ::malloc(size);
        printf("alloc %lu bytes at %p\n", size, ptr);
        return ptr;
    }
    
    void* DefaultSpineExtension::_calloc(size_t size, const char* file, int line) {
		if (size == 0)
			return 0;

        void* ptr = ::malloc(size);
        if (ptr) {
            memset(ptr, 0, size);
        }
        printf("calloc %lu bytes at %p\n", size, ptr);
        return ptr;
    }
    
    void* DefaultSpineExtension::_realloc(void* ptr, size_t size, const char* file, int line) {
        void* mem = NULL;
		if (size == 0)
			return 0;
        if (ptr == NULL)
            mem = ::malloc(size);
        else
            mem = ::realloc(ptr, size);
        printf("realloc %lu bytes from %p to %p\n", size, ptr, mem);
        return mem;
    }
    
    void DefaultSpineExtension::_free(void* mem, const char* file, int line) {
        printf("free %p\n", mem);
        ::free(mem);
    }
    
    DefaultSpineExtension::DefaultSpineExtension() : SpineExtension() {
        // Empty
    }
}