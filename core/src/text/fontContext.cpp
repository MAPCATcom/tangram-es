#include "fontContext.h"
#define GLFONTSTASH_IMPLEMENTATION
#include "glfontstash.h"

FontContext::FontContext() : FontContext(512) {}

FontContext::FontContext(int _atlasSize) : m_contextMutex(std_patch::make_unique<std::mutex>()) {
    initFontContext(_atlasSize);
}

FontContext::~FontContext() {
    m_atlas->destroy();
    glfonsDelete(m_fsContext);
}

std::shared_ptr<TextBuffer> FontContext::genTextBuffer() {
    return std::shared_ptr<TextBuffer>(new TextBuffer(m_fsContext));
}

const std::unique_ptr<Texture>& FontContext::getAtlas() const {
    return m_atlas;
}

void FontContext::getProjection(float* _projectionMatrix) const {
    glfonsProjection(m_fsContext, _projectionMatrix);
}

void FontContext::setScreenSize(int _width, int _height) {
    glfonsScreenSize(m_fsContext, _width, _height);
}

void FontContext::clearState() {
    fonsClearState(m_fsContext);
}

void FontContext::useBuffer(const std::shared_ptr<TextBuffer>& _textBuffer) {
    m_currentBuffer = _textBuffer;
}

void FontContext::setSignedDistanceField(float _blurSpread) {
    fonsSetBlur(m_fsContext, _blurSpread);
    fonsSetBlurType(m_fsContext, FONS_EFFECT_DISTANCE_FIELD);
}

void FontContext::lock() {
    m_contextMutex->lock();
}

void FontContext::unlock() {
    m_contextMutex->unlock();
}

std::shared_ptr<TextBuffer> FontContext::getCurrentBuffer() {
    return m_currentBuffer.lock();
}

bool FontContext::addFont(std::string _fontFile, std::string _name) {
    if (m_fonts.find(_name) != m_fonts.end()) {
        return true;
    }

    unsigned int dataSize;
    unsigned char* data = bytesFromResource(_fontFile.c_str(), &dataSize);
    m_font = fonsAddFont(m_fsContext, "droid-serif", data, dataSize);

    if (m_font == FONS_INVALID) {
        logMsg("[FontContext] Error loading font file %s\n", _fontFile.c_str());
        return false;
    }

    m_fonts[_name] = m_font;

    return true;
}

void FontContext::setFont(std::string _name, int size) {
    auto it = m_fonts.find(_name);

    if (it != m_fonts.end()) {
        fonsSetSize(m_fsContext, size);
        fonsSetFont(m_fsContext, it->second);
    } else {
        logMsg("[FontContext] Could not find font %s\n", _name.c_str());
    }
}

void updateAtlas(void* _userPtr, unsigned int _xoff, unsigned int _yoff,
                 unsigned int _width, unsigned int _height, const unsigned int* _pixels) {

    FontContext* fontContext = static_cast<FontContext*>(_userPtr);
    fontContext->m_atlas->setSubData(static_cast<const GLuint*>(_pixels), _xoff, _yoff, _width, _height);
}

void FontContext::initFontContext(int _atlasSize) {
    GLFONSparams params;
    
    m_atlas = std::unique_ptr<Texture>(new Texture(_atlasSize, _atlasSize));
    
    params.updateAtlas = updateAtlas;

    m_fsContext = glfonsCreate(_atlasSize, _atlasSize, FONS_ZERO_TOPLEFT, params, (void*) this);
}
