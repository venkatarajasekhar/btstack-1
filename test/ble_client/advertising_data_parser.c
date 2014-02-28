
//*****************************************************************************
//
// test rfcomm query tests
//
//*****************************************************************************


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ad_parser.h"

#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

static uint8_t ad_data[] =   {0x02, 0x01, 0x05, 0x03, 0x02, 0xF0, 0xFF};

static uint8_t ad_uuid16[] = {0x02, 0x04, 0x78, 0x56, 0x34, 0x12, 
                              0x02, 0x04, 0xf0, 0xde, 0xbc, 0x9a};

static uint8_t uuid16[] = { 0x12, 0x34, 
                            0x56, 0x78, 
                            0x9a, 0xbc, 
                            0xde, 0xf0 };

static uint8_t ad_uuid128[] = {0x06, 0x10, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12, 0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12}; 
                              
static uint8_t uuid128[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0, 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0} ;


TEST_GROUP(ADParser){
};


TEST(ADParser, TestDataParsing){
    ad_context_t context;
    uint8_t  expected_len[] = {1, 2};
    uint8_t  expected_type[] = {0x01, 0x02};
    uint8_t  expected_data[][2] = {{0x05, 0x00}, {0xF0, 0xFF}};

    int i = 0;
    uint8_t  ad_len = sizeof(ad_data);

    for (ad_iterator_init(&context, ad_len, ad_data) ; ad_iterator_has_more(&context) ; ad_iterator_next(&context)){
        uint8_t data_type = ad_iterator_get_data_type(&context);
        uint8_t data_len  = ad_iterator_get_data_len(&context);
        uint8_t * data    = ad_iterator_get_data(&context);
        
        CHECK_EQUAL(expected_len[i],  data_len);
        CHECK_EQUAL(expected_type[i], data_type);

        int j;
        for (j = 0; j < data_len; j++){
            CHECK_EQUAL(expected_data[i][j], data[j]);
        }
        i++; 
    }
}

TEST(ADParser, TestHasUUID){

}

int main (int argc, const char * argv[]){
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
