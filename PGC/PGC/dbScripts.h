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

const char* crt_tbl_APP_BOOK_724 = "CREATE TABLE APP_BOOK (BOOKNO INT, BOOKNAME CHARACTER(100),PRIMARY KEY (BOOKNO));";
const char* ppl_tbl_APP_BOOK_724 = "INSERT INTO APP_BOOK (BOOKNO,BOOKNAME) Select CAST(F1 AS INTEGER), F2 from SYTBLENT WHERE SKEY LIKE 'APPVIEWL%'  AND  SUBSTRING (SKEY FROM 10 FOR 4) = '0000' AND 'APPVIEWNE' || SUBSTRING (SKEY FROM 10 FOR 6) IN (SELECT SKEY FROM SYTBLENT);";
const char* dlt_tbl_APP_BOOK_724 = "DROP TABLE APP_BOOK;";

const char* crt_tbl_ITEMS_725 = "CREATE TABLE ITEMS ( ITEMCODE CHARACTER(5), DESCR CHARACTER (90)) ;";
const char* ppl_tbl_ITEMS_725 = "INSERT INTO ITEMS(ITEMCODE, DESCR) SELECT SUBSTRING(SKEY FROM 10 FOR 5), SUBSTRING(F1 FROM 1 FOR 90) FROM SYTBLENT WHERE SUBSTRING(SKEY FROM 1 FOR 9) = 'ITEMNUMBE';";
const char* dlt_tbl_ITEMS_725 = "DROP TABLE ITEMS;";

const char* crt_tbl_ITEM_ANALYSIS_726 = "CREATE TABLE ITEM_ANALYSIS ( ITEMCODE CHARACTER(5), USAGE BIGINT, AMOUNT BIGINT);";
//const char* ppl_tbl_ITEM_ANALYSIS_726_org= "INSERT INTO ITEM_ANALYSIS (ITEMCODE,USAGE,AMOUNT) Select substring(itemcode from 1 for 5)  as it, sum(frequency) as tms, sum(amount) as amt from pbarcmas  where transtype = 1 and deleted <> -1 and entrydate   between date'" & Format($startDate, "YYYY-MM-DD") & "'" & " and date'" & Format($endDate, "YYYY-MM-DD") & "'" & " group by itemcode  ;";
const char* ppl_tbl_ITEM_ANALYSIS_726 = "INSERT INTO ITEM_ANALYSIS (ITEMCODE,USAGE,AMOUNT) Select substring(itemcode from 1 for 5)  as it, sum(frequency) as tms, sum(amount) as amt from pbarcmas  where transtype = 1 and deleted <> -1 and entrydate between date'%1' and date'%2' group by itemcode;";
const char* dlt_tbl_ITEM_ANALYSIS_726 = "DROP TABLE ITEM_ANALYSIS";

