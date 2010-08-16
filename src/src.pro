TARGET = QLibOA
TEMPLATE = lib
DESTDIR = ../lib

HEADERS += \
    QLibOAUtil.h \
    QLibOAToken.h \
    QLibOASignatureHMAC.h \
    QLibOASignature.h \
    QLibOARequest.h \
    QLibOAConsumer.h \
    QLibOASignaturePlainText.h \
    QLibOACommon.h

SOURCES += \
    QLibOAUtil.cpp \
    QLibOAToken.cpp \
    QLibOASignatureHMAC.cpp \
    QLibOARequest.cpp \
    QLibOAConsumer.cpp

CONFIG(debug_and_release) {
    build_pass:CONFIG(debug, debug|release) {
        TARGET = $$join(TARGET,,,d)
    }
}
