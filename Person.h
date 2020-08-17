#pragma once
struct AddressTmpl
{
    char sStreet[51];
    char sCity[51];
    char sCountry[51];
};

enum Gender
{
    Male = 1,
    Female = 2
};

struct PersonTmpl
{
    int nPersonID;

    char chRecordType;
#define REC_TYPE_PERSONAL  1
#define REC_TYPE_HOME      2
#define REC_TYPE_WORK      3

    union
    {
        struct /* record type 1 */
        {
            char sFirstName[31];
            char sLastName[32];
            char sBirthdate[11]; /* YYYY/MM/DD date format */
            Gender theGender;
        }PersonalInfo;

        struct /* record type 2 */
        {
            struct AddressTmpl homeAddress;
            char sPhone[31];
            char sEmail[51];
        }HomeDetails;

        struct /* record type 3 */
        {
            char sCompany[51];
            struct AddressTmpl workAddress;
            char sPhone[31];
            char sFax[31];
            char sEmail[51];
        }WorkDetails;
    }Details;
};

