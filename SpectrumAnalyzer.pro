#-------------------------------------------------
#
# Project created by QtCreator 2015-07-30T20:28:30
#
#-------------------------------------------------

include(common.pri)

equals(TARGET, SpectrumAnalyzer) {
    include(app.pri)
}

equals(TARGET, SpectrumAnalyzerUt) {
    include(ut.pri)
}

DISTFILES += \
    common.pri \
    app.pri
