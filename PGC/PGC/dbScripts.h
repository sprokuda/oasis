#pragma once

const char* crt_tbl_FIRST_INV_721 = "CREATE TABLE FIRST_INV( PTNO CHARACTER(6), INV DATE)";
const char* ppl_tbl_FIRST_INV_721 = "INSERT INTO FIRST_INV SELECT PATNUMBER , min(consultdate)  from pbarcmas where deleted <> -1 and transtype =1 group by patnumber;";
const char* dlt_tbl_FIRST_INV_721 = "DROP TABLE FIRST_INV;";
//
const char* crt_tbl_LAST_INV_722 = "CREATE TABLE LAST_INV( PTNO CHARACTER(6), LASTVISITDATE DATE);";
const char* ppl_tbl_LAST_INV_722 = "INSERT INTO LAST_INV SELECT PATNUMBER , max(consultdate)  from pbarcmas where deleted <> -1 and transtype =1 group by patnumber;";
const char* dlt_tbl_LAST_INV_722 = "DROP TABLE LAST_INV;";

const char* crt_tbl_FUT_APP_723 = "CREATE TABLE FUT_APP( PTNO CHARACTER(6));";
const char* ppl_tbl_FUT_APP_723 = "INSERT INTO FUT_APP SELECT DISTINCT PATNUMBER from PAAPPLNS where SKEY > SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 6 FOR 4) || SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 11 FOR 2) || SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 14 FOR 2);";
const char* dlt_tbl_FUT_APP_723 = "DROP TABLE FUT_APP;";

