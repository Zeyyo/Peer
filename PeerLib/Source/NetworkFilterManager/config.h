#pragma once

#define FILTER_ALREADY_EXISTS 0x97
#define FILTER_ERROR 0x98
#define FILTER_SUCCESS 0x99

#define AVAST_AV_SERVER 0x1
constexpr char cexprAvastAVServer[] = "93.184.215.14";
const GUID AVAST_SERVER_FILTER_KEY = { 0x87654321, 0xABCDE, 0xFEDC, { 0x98, 0x76, 0x54, 0x32, 0x10, 0xAB, 0xCD, 0xEF } };

#define AVAST_AV_APP_SERVER 0x2
constexpr char cexprAvastAppAVServer[] = "D:\\Library\\SideProblems\\RedirectTest\\x64\\Debug\\RedirectTest.exe";

const GUID AVAST_APP_SERVER_FILTER_KEY = { 0xABCD1234, 0x5678, 0x9ABC, { 0xDE, 0xFA, 0xCE, 0xBA, 0xBE, 0xEF, 0x12, 0x34 } };