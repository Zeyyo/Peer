#pragma once

#pragma region AVAST_SVCs

#define AVAST_AV 0x1
#define AVAST_ANTI_TRACK_SVC 0x2
#define AVAST_CLEANUP_SVC 0x3
#define AVAST_DRIVER_UPD_SVC 0x4
#define AVAST_FIREWALL 0x5
#define AVAST_TOOLS 0x6
#define AVAST_WSC_REPORTER 0x7

constexpr char cexprAvastAV[] = "avast! Antivirus";
constexpr char cexprAvastAntiTrackSvc[] = "AvastAntiTrackSvc";
constexpr char cexprAvastCleanupPSvc[] = "CleanupPSvc";
constexpr char cexprAvastDriverUpdSvc[] = "DriverUpdSvc";
constexpr char cexprAvastFirewall[] = "avast! Firewall";
constexpr char cexprAvastTools[] = "avast! Tools";
constexpr char cexprAvastWscReporter[] = "AvastWscReporter";

#pragma endregion AVAST_SVCs

#pragma region GOOGLE_SVCs

#define GOOGLE_UPDATER_INTERNAL_SVC 0x8
#define GOOGLE_UPDATER_SVC 0x9

constexpr char cexprGoogleUpdaterInternalService[] = "GoogleUpdaterInternalService127.0.6490.0";
constexpr char cexprGoogleUpdaterService[] = "GoogleUpdaterService127.0.6490.0";

#pragma endregion GOOGLE_SVCs