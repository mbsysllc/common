#include <gtest/gtest.h>

#include <common/value.h>

template <typename T, typename U>
void CheckValue(U* (*create_ptr)(T t), bool (U::*get_ptr)(T* t) const, T val, common::Value::Type vt) {
  U* cval = create_ptr(val);
  ASSERT_TRUE(cval && cval->GetType() == vt);
  T val_res;
  ASSERT_TRUE((cval->*get_ptr)(&val_res));
  ASSERT_EQ(val_res, val);
  delete cval;
}

TEST(Value, create_and_get_simple_type) {
  common::Value* val_null = common::Value::CreateNullValue();
  ASSERT_TRUE(val_null && val_null->GetType() == common::Value::TYPE_NULL);

  CheckValue(&common::Value::CreateBooleanValue, &common::FundamentalValue::GetAsBoolean, true,
             common::Value::TYPE_BOOLEAN);
  CheckValue(&common::Value::CreateIntegerValue, &common::FundamentalValue::GetAsInteger, 11,
             common::Value::TYPE_INTEGER);
  CheckValue(&common::Value::CreateUIntegerValue, &common::FundamentalValue::GetAsUInteger, 321U,
             common::Value::TYPE_UINTEGER);
  CheckValue(&common::Value::CreateLongIntegerValue, &common::FundamentalValue::GetAsLongInteger, 1341L,
             common::Value::TYPE_LONG_INTEGER);
  CheckValue(&common::Value::CreateULongIntegerValue, &common::FundamentalValue::GetAsULongInteger, 3231UL,
             common::Value::TYPE_ULONG_INTEGER);
  CheckValue(&common::Value::CreateLongLongIntegerValue, &common::FundamentalValue::GetAsLongLongInteger, 161LL,
             common::Value::TYPE_LONG_LONG_INTEGER);
  CheckValue(&common::Value::CreateULongLongIntegerValue, &common::FundamentalValue::GetAsULongLongInteger, 3211ULL,
             common::Value::TYPE_ULONG_LONG_INTEGER);
  CheckValue(&common::Value::CreateDoubleValue, &common::FundamentalValue::GetAsDouble, 11.5,
             common::Value::TYPE_DOUBLE);
}

TEST(Value, create_and_get_complex_type) {
  const std::string data = "data";
  common::Value* val_string = common::Value::CreateStringValue(data);
  ASSERT_TRUE(val_string && val_string->GetType() == common::Value::TYPE_STRING);
  std::string data2;
  ASSERT_TRUE(val_string->GetAsString(&data2));
  ASSERT_EQ(data, data2);

  common::Value* val_arr = common::Value::CreateArrayValue();
  ASSERT_TRUE(val_arr && val_arr->GetType() == common::Value::TYPE_ARRAY);

  const common::byte_array_t bt = {0, 1};
  common::Value* val_barr = common::Value::CreateByteArrayValue(bt);
  ASSERT_TRUE(val_barr && val_barr->GetType() == common::Value::TYPE_BYTE_ARRAY);
  common::byte_array_t bt2;
  ASSERT_TRUE(val_barr->GetAsByteArray(&bt2));
  ASSERT_EQ(bt2, bt);

  common::Value* val_set = common::Value::CreateSetValue();
  ASSERT_TRUE(val_set && val_set->GetType() == common::Value::TYPE_SET);

  common::Value* val_zset = common::Value::CreateZSetValue();
  ASSERT_TRUE(val_zset && val_zset->GetType() == common::Value::TYPE_ZSET);

  common::Value* val_hash = common::Value::CreateHashValue();
  ASSERT_TRUE(val_hash && val_hash->GetType() == common::Value::TYPE_HASH);

  const std::string err_descr = "err";
  const common::Value::ErrorsType ert = common::Value::E_INTERRUPTED;
  const common::logging::LEVEL_LOG lg = common::logging::L_INFO;
  common::ErrorValue* val_error = common::Value::CreateErrorValue(err_descr, ert, lg);
  ASSERT_TRUE(val_error && val_error->GetType() == common::Value::TYPE_ERROR && val_error->IsError());
  ASSERT_EQ(val_error->GetDescription(), err_descr);
  ASSERT_EQ(val_error->GetErrorType(), ert);
  ASSERT_EQ(val_error->GetLevel(), lg);
}
