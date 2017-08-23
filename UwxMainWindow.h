/******************************************************************************
** Copyright (C) 2015-2017 Laird
**
** Project: UwTerminalX
**
** Module: UwxMainWindow.h
**
** Notes:
**
** License: This program is free software: you can redistribute it and/or
**          modify it under the terms of the GNU General Public License as
**          published by the Free Software Foundation, version 3.
**
**          This program is distributed in the hope that it will be useful,
**          but WITHOUT ANY WARRANTY; without even the implied warranty of
**          MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**          GNU General Public License for more details.
**
**          You should have received a copy of the GNU General Public License
**          along with this program.  If not, see http://www.gnu.org/licenses/
**
*******************************************************************************/
#ifndef UWXMAINWINDOW_H
#define UWXMAINWINDOW_H

/******************************************************************************/
// Include Files
/******************************************************************************/
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMenu>
#include <QClipboard>
#include <QMimeData>
#include <QFileDialog>
#include <QScrollBar>
#include <QProcess>
#include <QTimer>
#include <QRegularExpression>
#include <QStringList>
#include <QMessageBox>
#include <QFile>
#include <QKeyEvent>
#include <QFontDialog>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTextDocumentFragment>
#include <QTime>
#include <QDate>
#include <QElapsedTimer>
#include <QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QFileInfo>
#include <QHostInfo>
#include <QStringRef>
//Need cmath for std::ceil function
#include <cmath>
#if TARGET_OS_MAC
#include "QStandardPaths"
#endif
#include "LrdScrollEdit.h"
#include "UwxPopup.h"
#include "LrdLogger.h"
#if SKIPAUTOMATIONFORM != 1
#include "UwxAutomation.h"
#endif
#if SKIPERRORCODEFORM != 1
#include "UwxErrorCode.h"
#endif
#if SKIPSCRIPTINGFORM != 1
#include "UwxScripting.h"
#endif
#include "UwxEscape.h"

/******************************************************************************/
// Defines
/******************************************************************************/
#ifndef QT_NO_SSL
    #define UseSSL //By default enable SSL if Qt supports it (requires OpenSSL runtime libraries). Comment this line out to build without SSL support or if you get errors when communicating with the server
#endif

/******************************************************************************/
// Constants
/******************************************************************************/
const QString ServerHost                      = "uwterminalx.no-ip.org"; //Hostname/IP of online xcompile server
//Constants for various file download functions
const qint8 MODE_COMPILE                      = 1;
const qint8 MODE_COMPILE_LOAD                 = 2;
const qint8 MODE_COMPILE_LOAD_RUN             = 3;
const qint8 MODE_LOAD                         = 4;
const qint8 MODE_LOAD_RUN                     = 5;
const qint8 MODE_SERVER_COMPILE               = 9;
const qint8 MODE_SERVER_COMPILE_LOAD          = 10;
const qint8 MODE_SERVER_COMPILE_LOAD_RUN      = 11;
const qint8 MODE_CHECK_ERROR_CODE_VERSIONS    = 14;
const qint8 MODE_CHECK_UWTERMINALX_VERSIONS   = 15;
const qint8 MODE_UPDATE_ERROR_CODE            = 16;
const qint8 MODE_CHECK_FIRMWARE_VERSIONS      = 17;
const qint8 MODE_CHECK_FIRMWARE_SUPPORT       = 18;
//Constants for version and functions
const QString UwVersion                       = "1.08w"; //Version string
//Constants for timeouts and streaming
const qint16 FileReadBlock                    = 512;     //Number of bytes to read per block when streaming files
const qint16 StreamProgress                   = 10000;   //Number of bytes between streaming progress updates
const qint16 BatchTimeout                     = 4000;    //Time (in ms) to wait for getting a response from a batch command for
const qint16 PrePostXCompTimeout              = 15000;   //Time (in ms) to allow a pre/post XCompilation process to execute for
const qint16 ModuleTimeout                    = 4000;    //Time (in ms) that a download stage command/process times out (module)
const qint8 MaxOldDevNameSize                 = 8;       //Size (in characters) to allow for older module device names (characters past this point will be chopped off)
const qint8 MaxDevNameSize                    = 18;      //Size (in characters) to allow for a module device name (characters past this point will be chopped off)
const qint16 AutoBaudTimeout                  = 1200;    //Time (in ms) to wait before checking the next baud rate when automatically detecting the module's baud rate
//Constants for default config values
const QString DefaultLogFile                  = "UwTerminalX.log";
const bool DefaultLogMode                     = 0;
const bool DefaultLogEnable                   = 0;
const QString DefaultCompilerDir              = "compilers/";
const bool DefaultCompilerSubDirs             = 0;
const bool DefaultDelUWCAfterDownload         = 0;
const bool DefaultSysTrayIcon                 = 1;
const qint16 DefaultSerialSignalCheckInterval = 50;
const bool DefaultPrePostXCompRun             = 0;
const bool DefaultPrePostXCompFail            = 0;
const bool DefaultPrePostXCompMode            = 0;
const QString DefaultPrePostXCompPath         = "";
const bool DefaultOnlineXComp                 = 1;
const qint16 DefaultTextUpdateInterval        = 80;
const bool DefaultSkipDownloadDisplay         = 1;
const bool DefaultSSLEnable                   = 1;
const bool DefaultShowFileSize                = 1;
const bool DefaultConfirmClear                = 1;
const bool DefaultShiftEnterLineSeparator     = 1;
const bool DefaultLicenceCheckMode            = 1;
//Constants the protocol
#ifndef UseSSL
    //HTTP
    const QString WebProtocol = "http";
#endif
const qint8 FilenameIndexApplication          = 0;
const qint8 FilenameIndexOthers               = 1;
//Constants for right click menu options
const qint8 MenuActionXCompile                = 1;
const qint8 MenuActionXCompileLoad            = 2;
const qint8 MenuActionXCompileLoadRun         = 3;
const qint8 MenuActionLoad                    = 4;
const qint8 MenuActionLoadRun                 = 5;
const qint8 MenuActionErrorHex                = 6;
const qint8 MenuActionErrorInt                = 7;
const qint8 MenuActionLoopback                = 8;
const qint8 MenuActionLoad2                   = 9;
const qint8 MenuActionEraseFile               = 10;
const qint8 MenuActionDir                     = 11;
const qint8 MenuActionRun                     = 12;
const qint8 MenuActionDebug                   = 13;
const qint8 MenuActionDataFile                = 14;
const qint8 MenuActionEraseFile2              = 15;
const qint8 MenuActionClearFilesystem         = 16;
const qint8 MenuActionMultiDataFile           = 17;
const qint8 MenuActionStreamFile              = 18;
const qint8 MenuActionFont                    = 19;
const qint8 MenuActionRun2                    = 20;
const qint8 MenuActionAutomation              = 21;
const qint8 MenuActionScripting               = 22;
const qint8 MenuActionBatch                   = 23;
const qint8 MenuActionClearModule             = 24;
const qint8 MenuActionClearDisplay            = 25;
const qint8 MenuActionClearRxTx               = 26;
const qint8 MenuActionCopy                    = 27;
const qint8 MenuActionCopyAll                 = 28;
const qint8 MenuActionPaste                   = 29;
const qint8 MenuActionSelectAll               = 30;
//Constants for balloon (notification area) icon options
const qint8 BalloonActionShow                 = 1;
const qint8 BalloonActionExit                 = 2;
//Constants for speed test menu
const qint8 SpeedMenuActionRecv               = 1;
const qint8 SpeedMenuActionSend               = 2;
const qint8 SpeedMenuActionSendRecv           = 3;
const qint8 SpeedMenuActionSendRecv5Delay     = 4;
const qint8 SpeedMenuActionSendRecv10Delay    = 5;
const qint8 SpeedMenuActionSendRecv15Delay    = 6;
const qint8 SpeedModeInactive                 = 0b00;
const qint8 SpeedModeRecv                     = 0b01;
const qint8 SpeedModeSend                     = 0b10;
const qint8 SpeedModeSendRecv                 = 0b11;
//Constants for the selector tab
const qint8 TabTerminal                       = 0;
const qint8 TabConfig                         = 1;
const qint8 TabSpeedTest                      = 2;
const qint8 TabUpdate                         = 3;
const qint8 TabAbout                          = 4;
const qint8 TabLogs                           = 5;
const qint8 TabEditor                         = 6;
//Constants for speed testing
const qint16 SpeedTestChunkSize               = 512;  //Maximum number of bytes to send per chunk when speed testing
const qint16 SpeedTestMinBufSize              = 128;  //Minimum buffer size when speed testing, when there are less than this number of bytes in the output buffer it will be topped up
const qint16 SpeedTestStatUpdateTime          = 500;  //Time (in ms) between status updates for speed test mode

/******************************************************************************/
// Forward declaration of Class, Struct & Unions
/******************************************************************************/
namespace Ui
{
    class MainWindow;
}

//Structure used for holding information on online XCompiled file locations
typedef struct
{
    QString strFilename; //Filename
    qint16 iStartingLine; //Starting line that file was put on
    qint16 iEndingLine; //Ending line that file's last data was put on
    qint8 iLineSpaces;
} FileSStruct;

//Enum used for specifying type of data
enum class BitByteTypes
{
    TypeBytes,
    TypeDataBits,
    TypeAllBits
};

/******************************************************************************/
// Class definitions
/******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(
        QWidget *parent = 0
        );
    ~MainWindow(
        );

public slots:
    void
    SerialRead(
        );
    void
    MenuSelected(
        QAction* qaAction
        );
    void
    balloontriggered(
        QAction* qaAction
        );
    void
    DevRespTimeout(
        );
#if defined(_WIN32) || defined(WIN32)
    //_WIN32 isn't defined when MOC is ran but WIN32 is.
    void
    process_finished(
        int intExitCode,
        QProcess::ExitStatus esExitStatus
        );
#endif
    void
    SerialStatusSlot(
        );
    void
    SerialError(
        QSerialPort::SerialPortError speErrorCode
        );
    void
    EnterPressed(
        );
    void
    KeyPressed(
        QChar chrKeyValue
        );
    void
    SerialBytesWritten(
        qint64 intByteCount
        );
    void
    SerialPortClosing(
        );
    void
    MessagePass(
        QByteArray baDataString,
        bool bEscapeString,
        bool bFromScripting
        );
    void
    SpeedMenuSelected(
        QAction* qaAction
        );
    quint64
    BitsBytesConvert(
        quint64 iCount,
        BitByteTypes bbtFrom,
        BitByteTypes bbtTo
        );

private slots:
    void
    on_btn_Accept_clicked(
        );
    void
    on_selector_Tab_currentChanged(
        int intIndex
        );
    void
    on_btn_Connect_clicked(
        );
    void
    on_btn_TermClose_clicked(
        );
    void
    on_btn_Refresh_clicked(
        );
    void
    on_btn_TermClear_clicked(
        );
    void
    on_btn_Duplicate_clicked(
        );
    void
    on_text_TermEditData_customContextMenuRequested(
        const QPoint &pos
        );
    void
    on_check_Break_stateChanged(
        );
    void
    on_check_RTS_stateChanged(
        );
    void
    on_check_DTR_stateChanged(
        );
    void
    on_check_Line_stateChanged(
        );
    void
    closeEvent(
        QCloseEvent *closeEvent
        );
    void
    on_btn_Cancel_clicked(
        );
    void
    UpdateReceiveText(
        );
    void
    BatchTimeoutSlot(
        );
    void
    on_combo_COM_currentIndexChanged(
        int intIndex
        );
    void
    replyFinished(
        QNetworkReply* nrReply
        );
#ifdef UseSSL
    void
    sslErrors(
        QNetworkReply*,
        QList<QSslError>
        );
#endif
    void
    on_check_PreXCompRun_stateChanged(
        int intChecked
        );
    bool
    RunPrePostExecutable(
        QString strFilename
        );
    void
    on_btn_PreXCompSelect_clicked(
        );
    void
    on_radio_XCompPre_toggled(
        bool bChecked
        );
    void
    on_radio_XCompPost_toggled(
        bool bChecked
        );
    void
    on_check_PreXCompFail_stateChanged(
        int bChecked
        );
    void
    on_edit_PreXCompFilename_editingFinished(
        );
    void
    on_btn_GitHub_clicked(
        );
    void
    on_check_OnlineXComp_stateChanged(
        int bChecked
        );
    QList<QString>
    SplitFilePath(
        QString strFilename
        );
    void
    on_btn_ErrorCodeUpdate_clicked(
        );
    void
    on_btn_UwTerminalXUpdate_clicked(
        );
    void
    on_check_Echo_stateChanged(
        int bChecked
        );
    void
    on_btn_ErrorCodeDownload_clicked(
        );
    void
    on_combo_PredefinedDevice_currentIndexChanged(
        int intIndex
        );
    void
    on_btn_PredefinedAdd_clicked(
        );
    void
    on_btn_PredefinedDelete_clicked(
        );
    void
    DroppedFile(
        QString strFilename
        );
    void
    on_btn_SaveDevice_clicked(
        );
    void
    on_btn_ModuleFirmware_clicked(
        );
    void
    ContextMenuClosed(
        );
    bool
    event(
        QEvent *evtEvent
        );
    void
    on_btn_LogFileSelect_clicked(
        );
    void
    on_edit_LogFile_editingFinished(
        );
    void
    on_check_LogEnable_stateChanged(
        int intChecked
        );
    void
    on_check_LogAppend_stateChanged(
        int intChecked
        );
    void
    on_btn_Help_clicked(
        );
    void
    on_combo_LogDirectory_currentIndexChanged(
        int
        );
    void
    on_btn_LogRefresh_clicked(
        );
    void
    on_btn_Licenses_clicked(
        );
    void
    on_btn_OnlineXComp_Supported_clicked(
        );
    void
    on_check_SkipDL_stateChanged(
        int
        );
    bool
    LookupDNSName(
        );
    void
    on_btn_WebBrowse_clicked(
        );
    void
    on_btn_EditViewFolder_clicked(
        );
    void
    on_combo_EditFile_currentIndexChanged(
        int
        );
    void
    on_btn_EditSave_clicked(
        );
    void
    on_btn_EditLoad_clicked(
        );
#ifndef __APPLE__
    void
    on_btn_EditExternal_clicked(
        );
#endif
    void
    on_btn_LogViewExternal_clicked(
        );
    void
    on_btn_LogViewFolder_clicked(
        );
    void
    on_text_EditData_textChanged(
        );
    void
    on_combo_LogFile_currentIndexChanged(
        int
        );
    void
    on_btn_ReloadLog_clicked(
        );
#ifdef UseSSL
    void
    on_check_EnableSSL_stateChanged(
        int
        );
#endif
    void
    on_check_ShowFileSize_stateChanged(
        int
        );
    void
    on_btn_DetectBaud_clicked(
        );
    void
    DetectBaudTimeout(
        );
    void
    on_check_ConfirmClear_stateChanged(
        int
        );
    void
    on_check_LineSeparator_stateChanged(
        int
        );
#if SKIPERRORCODEFORM != 1
    void
    on_btn_Error_clicked(
        );
#endif
#if SKIPSCRIPTINGFORM != 1
    void
    ScriptStartRequest(
        );
    void
    ScriptFinished(
        );
#endif
    void
    on_check_SpeedRTS_stateChanged(
        int
        );
    void
    on_check_SpeedDTR_stateChanged(
        int
        );
    void
    on_btn_SpeedClear_clicked(
        );
    void
    on_btn_SpeedClose_clicked(
        );
    void
    on_btn_SpeedStart_clicked(
        );
    void
    on_btn_SpeedStop_clicked(
        );
    void
    OutputSpeedTestStats(
        );
    void
    on_combo_SpeedDataType_currentIndexChanged(
        int
        );
    void
    on_btn_SpeedCopy_clicked(
        );
    void
    UpdateSpeedTestValues(
        );
    void
    SpeedTestStartTimer(
        );
    void
    SpeedTestStopTimer(
        );
    void
    UpdateDisplayText(
        );
    void
    on_combo_SpeedDataDisplay_currentIndexChanged(
        int
        );
    void
    on_check_CheckLicense_stateChanged(
        int
        );

private:
    Ui::MainWindow *ui;
    void
    RefreshSerialDevices(
        );
    unsigned char
    CompileApp(
        unsigned char chMode
        );
    void
    UpdateImages(
        );
    void
    DoLineEnd(
        );
    void
    SerialStatus(
        bool bType
        );
    void
    OpenDevice(
        );
    void
    LoadFile(
        bool bToUWC
        );
    void
    RunApplication(
        );
    void
    LookupErrorCode(
        unsigned int intErrorCode
        );
    void
    FinishStream(
        bool bType
        );
    void
    FinishBatch(
        bool bType
        );
    QString
    AtiToXCompName(
        QString strAtiResp
        );
    void
    LoadSettings(
        );
    void
    UpdateSettings(
        int intMajor,
        int intMinor,
        QChar qcDelta
        );
    QString
    CleanFilesize(
        QString strFilename
        );
    QString
    RemoveZeros(
        QString strData
        );
    void
    SendSpeedTestData(
        int intMaxLength
        );
    void
    SpeedTestBytesWritten(
        qint64 intByteCount
        );
    void
    SpeedTestReceive(
        );
    void
    OutputSpeedTestAvgStats(
        qint64 lngElapsed
        );
    void
    StreamBatchContinue(
        QByteArray *baOrigData
        );
    void
    ClearFileDataList(
        );
    void
    SetLoopBackMode(
        bool bNewMode
        );

    //Private variables
    bool gbTermBusy; //True when compiling or loading a program or streaming a file (busy)
    bool gbStreamingFile; //True when a file is being streamed
    QSerialPort gspSerialPort; //Contains the handle for the serial port
    quint32 gintRXBytes; //Number of RX bytes
    quint32 gintTXBytes; //Number of TX bytes
    quint32 gintQueuedTXBytes; //Number of TX bytes that have been queued in buffer (not necesserially sent)
    unsigned char gchTermBusyLines; //Number of commands recieved (for sending applications)
    unsigned char gchTermMode; //What function is being ran when compiling
    unsigned char gchTermMode2; //Current sub-mode of download
    QString gstrTermFilename; //Holds the filename of the file to load
    QString gstrTermBusyData; //Holds the recieved data for checking
#ifdef _WIN32
    QProcess gprocCompileProcess; //Holds the data for the process to compile
#endif
    QImage gimEmptyCircleImage; //Holder for empty circle image
    QImage gimRedCircleImage; //Holder for red circle image
    QImage gimGreenCircleImage; //Holder for green circle image
    QImage gimUw16Image; //Holder for UwTerminal 16x16 icon
    QImage gimUw32Image; //Holder for UwTerminal 32x32 icon
    QPixmap *gpEmptyCirclePixmap; //Pixmap holder for empty circle image
    QPixmap *gpRedCirclePixmap; //Pixmap holder for red circle image
    QPixmap *gpGreenCirclePixmap; //Pixmap holder for green circle image
    QPixmap *gpUw32Pixmap; //Pixmap holder for UwTerminal 32x32 icon
    QPixmap *gpUw16Pixmap; //Pixmap holder for UwTerminal 16x16 icon
    QString gstrHexData; //Holds the hex data to be sent to the device
    QString gstrDownloadFilename; //Holds the inter-function download filename
    QTimer *gpSignalTimer; //Handle for a timer to update COM port signals
    QTimer gtmrDownloadTimeoutTimer; //Timer for module timeout indication
    LrdLogger *gpMainLog; //Handle to the main log file (if enabled/used)
    bool gbMainLogEnabled; //True if opened successfully (and enabled)
    QMenu *gpMenu; //Main menu
    QMenu *gpSMenu1; //Submenu 1
    QMenu *gpSMenu2; //Submenu 2
    QMenu *gpSMenu3; //Submenu 3
    QMenu *gpBalloonMenu; //Balloon menu
    QMenu *gpSpeedMenu; //Speed testing menu
    bool gbLoopbackMode; //True if loopback mode is enabled
    bool gbSysTrayEnabled; //True if system tray is enabled
    QSystemTrayIcon *gpSysTray; //Handle for system tray object
    bool gbIsUWCDownload; //Set to true when a UWC is being downloaded
    bool gbCTSStatus; //True when CTS is asserted
    bool gbDCDStatus; //True when DCD is asserted
    bool gbDSRStatus; //True when DSR is asserted
    bool gbRIStatus; //True when RI is asserted
    QFile *gpStreamFileHandle; //Handle for the file to stream data from
    quint32 gintStreamBytesSize; //The size of the file to stream in bytes
    quint32 gintStreamBytesRead; //The number of bytes read from the stream
    quint32 gintStreamBytesProgress; //The number of bytes when the next progress output should be made
    QByteArray gbaDisplayBuffer; //Buffer of data to display
    QElapsedTimer gtmrStreamTimer; //Counts how long a stream takes to send
    QTimer gtmrTextUpdateTimer; //Timer for slower updating of display buffer (but less display freezing)
    bool gbStreamingBatch; //True if batch file is being streamed
    QTimer gtmrBatchTimeoutTimer; //Timer for a batch command timeout
    QByteArray gbaBatchReceive; //Storage for batch data coming in
    QSettings *gpTermSettings; //Handle to settings
    QSettings *gpErrorMessages; //Handle to error codes
    QSettings *gpPredefinedDevice; //Handle to predefined devices
    QNetworkAccessManager *gnmManager; //Network access manager
    QNetworkReply *gnmrReply; //Network reply
    QString gstrDeviceID; //What the server compiler ID is
    bool gbFileOpened; //True when a file on the module has been opened
    QString gstrLastFilename[2]; //Holds the filenames of the last selected files
    QString gstrResolvedServer; //Holds the resolved hostname of the XCompile server
    bool gbEditFileModified; //True if the file in the editor pane has been modified, otherwise false
    int giEditFileType; //Type of file currently open in the editor
    bool gbErrorsLoaded; //True if error csv file has been loaded
    QTimer gtmrBaudTimer; //Timer for automatic baud rate detection timeout
    bool gbAutoBaud; //True if automatic baud rate detection is in progress
#ifdef UseSSL
    QString WebProtocol; //Holds HTTP or HTTPS depending on options selected
    QSslCertificate *sslcLairdSSLNew = NULL; //Holds the (newer) Laird SSL certificate
#endif
    PopupMessage *gpmErrorForm; //Error message form
#if SKIPAUTOMATIONFORM != 1
    UwxAutomation *guaAutomationForm; //Automation form
#endif
#if SKIPERRORCODEFORM != 1
    UwxErrorCode *gecErrorCodeForm; //Error code lookup form
#endif
#if SKIPSCRIPTINGFORM != 1
    UwxScripting *gusScriptingForm; //Scripting form
    bool gbScriptingRunning; //True if a script is running
#endif
    bool gbSpeedTestRunning; //True if speed test is running
    unsigned char gchSpeedTestMode; //What mode the speed test is (inactive, receive, send or send & receive)
    QElapsedTimer gtmrSpeedTimer; //Used for timing how long a speed test has been running
    QByteArray gbaSpeedDisplayBuffer; //Buffer of data to display for speed test mode
    QByteArray gbaSpeedMatchData; //Expected data to match in speed test mode
    QByteArray gbaSpeedReceivedData; //Received data from device in speed test mode
    QTimer gtmrSpeedTestStats; //Timer that runs every 250ms to update stats for speed test
    QTimer gtmrSpeedTestStats10s; //Timer that runs every 10 seconds to output 10s stats for speed test
    QTimer gtmrSpeedUpdateTimer; //Timer for slower updating of speed test buffer (but less display freezing)
    QTimer *gtmrSpeedTestDelayTimer; //Timer used for delay before sending data in speed test mode
    quint64 gintSpeedBytesReceived; //Number of bytes received from device in speed test mode
    quint64 gintSpeedBytesReceived10s; //Number of bytes received from device in the past 10 seconds in speed test mode
    quint64 gintSpeedBytesSent; //Number of bytes sent to the device in speed test mode
    quint64 gintSpeedBytesSent10s; //Number of bytes sent to the device in the past 10 seconds in speed test mode
    quint32 gintSpeedBufferCount; //Number of bytes waiting to be sent to the device (waiting in the buffer) in speed test mode
    quint32 gintSpeedTestMatchDataLength; //Length of MatchData
    quint32 gintSpeedTestReceiveIndex; //Current index for RecData
    quint32 gintSpeedTestStatErrors; //Number of errors in packets recieved in speed test mode
    quint32 gintSpeedTestStatSuccess; //Number of successful packets received in speed test mode
    quint32 gintSpeedTestStatPacketsSent; //Numbers of packets sent in speed test mode
    quint32 gintSpeedTestStatPacketsReceived; //Number of packets received in speed test mode
    quint8 gintSpeedTestDataBits; //Number of data bits (per byte) for speed testing
    quint8 gintSpeedTestStartStopParityBits; //Number of bits for start/stop/parity (per byte) for speed testing
    quint8 gintSpeedTestBytesBits; //Holds the current speed test combo selection option
    QList<FileSStruct *> lstFileData; //Holds a list of filenames and line numbers for the file currently being XCompiled
    quint8 gintDelayedSpeedTest; //Stores that delay before sending data in a speed test begins

protected:
    void dragEnterEvent(
        QDragEnterEvent *dragEvent
        );
    void dropEvent(
        QDropEvent *dropEvent
        );
};

#endif // UWXMAINWINDOW_H

/******************************************************************************/
// END OF FILE
/******************************************************************************/
