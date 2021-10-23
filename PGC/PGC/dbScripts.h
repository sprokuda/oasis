#pragma once

const char* crt_tbl_FIRST_INV_721 = "CREATE TABLE FIRST_INV( PTNO CHARACTER(6), INV DATE)";
const char* ppl_tbl_FIRST_INV_721 = "INSERT INTO FIRST_INV SELECT PATNUMBER , min(consultdate)  from pbarcmas where deleted <> -1 and transtype =1 group by patnumber;";
const char* dlt_tbl_FIRST_INV_721 = "DROP TABLE FIRST_INV;";
//
const char* crt_tbl_LAST_INV_722 = "CREATE TABLE LAST_INV( PTNO CHARACTER(6), LASTVISITDATE DATE);";
const char* ppl_tbl_LAST_INV_722 = "INSERT INTO LAST_INV SELECT PATNUMBER , max(consultdate)  from pbarcmas where deleted <> -1 and transtype =1 group by patnumber;";
const char* dlt_tbl_LAST_INV_722 = "DROP TABLE LAST_INV;";

const char* crt_tbl_FUT_APP_723 = "CREATE TABLE FUT_APP( PTNO CHARACTER(6));";
const char* ppl_tbl_FUT_APP_723 = "INSERT INTO FUT_APP SELECT DISTINCT PATNUMBER from PAAPPLNS where SKEY > SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 6 FOR 4) || "
									"SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 11 FOR 2) || SUBSTRING(CAST(CURRENT_DATE AS CHAR(16)) FROM 14 FOR 2);";
const char* dlt_tbl_FUT_APP_723 = "DROP TABLE FUT_APP;";

const char* crt_tbl_APP_BOOK_724 = "CREATE TABLE APP_BOOK (BOOKNO INT, BOOKNAME CHARACTER(100),PRIMARY KEY (BOOKNO));";
const char* ppl_tbl_APP_BOOK_724 = "INSERT INTO APP_BOOK (BOOKNO,BOOKNAME) Select CAST(F1 AS INTEGER), F2 from SYTBLENT WHERE SKEY LIKE 'APPVIEWL%' "
"									AND  SUBSTRING (SKEY FROM 10 FOR 4) = '0000' AND 'APPVIEWNE' || SUBSTRING (SKEY FROM 10 FOR 6) IN (SELECT SKEY FROM SYTBLENT);";
const char* dlt_tbl_APP_BOOK_724 = "DROP TABLE APP_BOOK;";

const char* crt_tbl_ITEMS_725 = "CREATE TABLE ITEMS ( ITEMCODE CHARACTER(5), DESCR CHARACTER (90)) ;";
const char* ppl_tbl_ITEMS_725 = "INSERT INTO ITEMS(ITEMCODE, DESCR) SELECT SUBSTRING(SKEY FROM 10 FOR 5), SUBSTRING(F1 FROM 1 FOR 90) FROM SYTBLENT WHERE SUBSTRING(SKEY FROM 1 FOR 9) = 'ITEMNUMBE';";
const char* dlt_tbl_ITEMS_725 = "DROP TABLE ITEMS;";

const char* crt_tbl_ITEM_ANALYSIS_726 = "CREATE TABLE ITEM_ANALYSIS ( ITEMCODE CHARACTER(5), USAGE BIGINT, AMOUNT BIGINT);";
//const char* ppl_tbl_ITEM_ANALYSIS_726_org= "INSERT INTO ITEM_ANALYSIS (ITEMCODE,USAGE,AMOUNT) Select substring(itemcode from 1 for 5)  as it, sum(frequency) as tms, sum(amount) as amt from pbarcmas  
//											"where transtype = 1 and deleted <> -1 and entrydate   between date'" & Format($startDate, "YYYY-MM-DD") & "'" & " and date'" & Format($endDate, "YYYY-MM-DD") & "'" & " group by itemcode; ";
const char* ppl_tbl_ITEM_ANALYSIS_726 = "INSERT INTO ITEM_ANALYSIS (ITEMCODE,USAGE,AMOUNT) Select substring(itemcode from 1 for 5)  as it, sum(frequency) as tms, sum(amount) as amt from pbarcmas "
										" where transtype = 1 and deleted <> -1 and entrydate between date'%1' and date'%2' group by itemcode;";
const char* dlt_tbl_ITEM_ANALYSIS_726 = "DROP TABLE ITEM_ANALYSIS";

const char* crt_tbl_CHURN_727 = "CREATE TABLE CHURN(PTNO CHARACTER(6), CHURNDATE DATE);";
const char* ppl_tbl_CHURN_727_1 = "INSERT INTO CHURN SELECT PTNO, LASTVISITDATE+INTERVAL'18'MONTH FROM LAST_INV   WHERE LASTVISITDATE BETWEEN CURRENT_DATE-INTERVAL'60'MONTH  AND CURRENT_DATE-INTERVAL'48'MONTH;";
const char* ppl_tbl_CHURN_727_2 = "INSERT INTO CHURN SELECT PTNO, LASTVISITDATE+INTERVAL'18'MONTH FROM LAST_INV   WHERE LASTVISITDATE BETWEEN CURRENT_DATE-INTERVAL'48'MONTH  AND CURRENT_DATE-INTERVAL'36'MONTH;";
const char* ppl_tbl_CHURN_727_3 = "INSERT INTO CHURN SELECT PTNO, LASTVISITDATE+INTERVAL'18'MONTH FROM LAST_INV   WHERE LASTVISITDATE BETWEEN CURRENT_DATE-INTERVAL'36'MONTH  AND CURRENT_DATE-INTERVAL'24'MONTH;";
const char* ppl_tbl_CHURN_727_4 = "INSERT INTO CHURN SELECT PTNO, LASTVISITDATE+INTERVAL'18'MONTH FROM LAST_INV   WHERE LASTVISITDATE BETWEEN CURRENT_DATE-INTERVAL'24'MONTH  AND CURRENT_DATE-INTERVAL'12'MONTH;";
const char* ppl_tbl_CHURN_727_5 = "INSERT INTO CHURN SELECT PTNO, LASTVISITDATE+INTERVAL'18'MONTH FROM LAST_INV   WHERE LASTVISITDATE BETWEEN CURRENT_DATE-INTERVAL'12'MONTH  AND CURRENT_DATE ;";
const char* dlt_tbl_CHURN_727 = "DROP TABLE CHURN;";

const char* crt_tbl_Production_728 = "CREATE TABLE Production( Prd DECIMAL (15,2)) ;";
const char* ppl_tbl_Production_728 = "";
const char* dlt_tbl_Production_728 = "DROP TABLE Production;";

const char* crt_fncn_unbkRecall_729 =
"@ \n"
"CREATE FUNCTION unbkRecall(PT VARCHAR(6), RD DATE) RETURNS INTEGER \n"
"READS SQL DATA \n"
"BEGIN \n"
"DECLARE unbooked INTEGER; \n"
"DECLARE app INTEGER; \n"
"SELECT  count(SKEY)  INTO app  from paapplns where patnumber = PT and entrydate between RD and RD + INTERVAL'30'DAY; \n"
"IF app > 0 then \n"
"SET unbooked = 0; \n"
"ELSE SET unbooked = 1; \n"
"END IF; \n"
"RETURN(Unbooked); \n"
"END \n"
"@ ";
const char* dlt_fncn_unbkRecall_729 = "DROP FUNCTION unbkRecall;";

const char* crt_fncn_lostRecall_7210 =
"@ "
"CREATE FUNCTION lostRecall(PT VARCHAR(6), RD DATE) RETURNS INTEGER "
"READS SQL DATA "
"BEGIN "
"DECLARE lost INTEGER;"
"DECLARE app INTEGER;"
"SELECT  count(SKEY)  INTO app  from paapplns where patnumber = PT and entrydate > RD - INTERVAL'1'DAY;"
"IF app > 0 then "
"SET lost = 0;"
"ELSE SET lost = 1;"
"END IF;"
"RETURN(lost);"
"END "
"@ ";
const char* dlt_fncn_lostRecall_7210 = "DROP FUNCTION lostRecall;";

const char* crt_fncn_apptbookEnd_7211 =
"@ "
"CREATE FUNCTION apptbookEnd() RETURNS INTEGER "
"READS SQL DATA "
"BEGIN "
"DECLARE St INTEGER;"
"DECLARE Hrs INTEGER;"
"DECLARE En INTEGER;"
"SELECT CAST(F1 AS INTEGER) INTO  St FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';"
"SELECT CAST(F2 AS INTEGER) INTO  Hrs FROM SYTBLENT WHERE SKEY = 'PAOPTIONE0000';"
"SET En = St + Hrs + 1;"
"RETURN(En);"
"END "
"@ ";
const char* dlt_fncn_apptbookEnd_7211 = "DROP FUNCTION apptbookEnd;";

const char* crt_fncn_apptUsed_7212 =
"@ "
"CREATE FUNCTION apptUsed(SKEY VARCHAR(20), usd INTEGER, appEnd INTEGER) RETURNS INTEGER "
"READS SQL DATA "
"BEGIN "
"DECLARE stHr INTEGER;"
"DECLARE maxDur INTEGER;"
"DECLARE usedTime INTEGER;"
//"\r"
"SET stHr = CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER);"
"SET maxDur = (appEnd - StHr) * 60;"
"IF usd > maxDur then "
"SET usedTime = maxDur;"
"ELSE SET usedTime = usd;"
"END IF;"
"RETURN(usedTime);"
"END "
"@ ";
const char* dlt_fncn_apptUsed_7212 = "DROP FUNCTION apptUsed;";

const char* crt_prcd_Production_7213 =
"@ "
"CREATE PROCEDURE  Production(IN A DATE, IN  B DATE) "
"MODIFIES SQL DATA "
"BEGIN "
"DECLARE invoice DECIMAL(15, 2);"
"DECLARE Adjust DECIMAL(15, 2);"
"DECLARE discount DECIMAL(15, 2);"
"DECLARE Writeoff DECIMAL(15, 2);"
"DECLARE Prod DECIMAL(15, 2);"
"DELETE FROM PRODUCTION;"
"SELECT   Sum(Amount) INTO invoice  from pbarcmas  where transtype = 1 and deleted <> -1 and entrydate  between A and B;"
"SELECT  Sum(Amount) INTO Adjust  from pbarcmas  where transtype = 2 and deleted <> -1 and entrydate  between A and B;"
"SELECT   Sum(Amount) INTO discount  from pbarcmas  where transtype = 4 and deleted <> -1 and entrydate  between A and B;"
"SELECT   Sum(Amount) INTO Writeoff from pbarcmas  where transtype = 5 and deleted <> -1 and entrydate  between A and B;"
"IF invoice is null then "
"set invoice = 0;"
"END IF;"
"IF Adjust is null then "
"set Adjust = 0;"
"END IF;"
"IF discount is null then "
"set discount = 0;"
"END IF;"
"IF Writeoff is null then "
"set Writeoff = 0;"
"END IF;"
"SET Prod = invoice + Adjust - discount - Writeoff;"
"INSERT INTO PRODUCTION(Prd) VALUES(Prod);"
"END "
"@ ";
const char* dlt_prcd_Production_7213 = "DROP PROCEDURE Production ;";


//"Select sum(timeused * $appSlot) / 60 as ptHr from paapplns where picturenumber <> $iconCan and picturenumber <> $iconNS AND SKEY BETWEEN " & "'" & Format($startDate, "YYYYMMDD") & "%' AND " & "'" & Format($endDate, "YYYYMMDD") & "%' and patnumber < > '000000' and (substring(skey from 13 for 4) = '$incCol1' OR substring(skey from 13 for 4) = '$incCol2' OR substring(skey from 13 for 4) = '$incCol3') and patnumber < >'' AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > $appStart - 1;"
const char* query_Hours_Worked_742 =
"Select sum(timeused * %1)/60 as ptHr from paapplns where picturenumber <> %2 "
"and picturenumber <> %3  AND SKEY BETWEEN '%4%'  AND '%5%' "
"and patnumber <> '000000' and (substring(skey from 13 for 4) = '%6' OR substring(skey from 13 for 4) = '%7' "
"OR substring(skey from 13 for 4) = '%8')  and patnumber <>'' AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > %9;";

const char* query_Hours_Worked_742_base =
"Select sum(timeused * %1)/60 as ptHr from paapplns where picturenumber <> %2 "
"AND picturenumber <> %3 "
"AND SKEY BETWEEN '%4%'  AND '%5%' "
"AND patnumber <> '000000' "
"AND patnumber <>'' "
"AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > %6 "
"AND ";
const char* append_book =
"substring(skey from 13 for 4) = '%1' OR ";

const char* query_Hours_Cancelled_743_base =
"Select sum(timeused * %1) / 60 as cnHr  from paapplns where(picturenumber = %2 OR  picturenumber = %3)"
"AND SKEY BETWEEN '%4%'  AND '%5%' "
"AND patnumber <> '000000' "
"AND patnumber <>'' "
"AND CAST(SUBSTRING(SKEY FROM 17 FOR 2)  AS INTEGER) > %6 "
"AND ";
