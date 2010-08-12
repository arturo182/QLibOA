TARGET = OAvis
TEMPLATE = lib
DESTDIR = ../lib

HEADERS += \
    OAvisUtil.h \
    OAvisToken.h \
    OAvisSignatureHMAC.h \
    OAvisSignature.h \
    OAvisRequest.h \
    OAvisConsumer.h \
    OAvisSignaturePlainText.h \
    OAvisCommon.h

SOURCES += \
    OAvisUtil.cpp \
    OAvisToken.cpp \
    OAvisSignatureHMAC.cpp \
    OAvisRequest.cpp \
    OAvisConsumer.cpp

CONFIG(debug_and_release) {
    build_pass:CONFIG(debug, debug|release) {
        TARGET = $$join(TARGET,,,d)
    }
}
