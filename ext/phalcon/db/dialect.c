
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/fcall.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2013 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Db\Dialect
 *
 * This is the base class to each database dialect. This implements
 * common methods to transform intermediate code into its RDBM related syntax
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Dialect) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Db, Dialect, phalcon, db_dialect, phalcon_db_dialect_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_db_dialect_ce, SL("_escapeChar"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Generates the SQL for LIMIT clause
 *
 *<code>
 * $sql = $dialect->limit('SELECT * FROM robots', 10);
 * echo $sql; // SELECT * FROM robots LIMIT 10
 *</code>
 *
 * @param string sqlQuery
 * @param int number
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, limit) {

	int number;
	zval *sqlQuery_param = NULL, *number_param = NULL, _0, _1;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &sqlQuery_param, &number_param);

		if (Z_TYPE_P(sqlQuery_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		sqlQuery = sqlQuery_param;

		number = zephir_get_intval(number_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, number);
	if (zephir_is_numeric(&_0)) {
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, number);
		ZEPHIR_CONCAT_VSV(return_value, sqlQuery, " LIMIT ", &_1);
		RETURN_MM();
	}
	RETURN_CTOR(sqlQuery);

}

/**
 * Returns a SQL modified with a FOR UPDATE clause
 *
 *<code>
 * $sql = $dialect->forUpdate('SELECT * FROM robots');
 * echo $sql; // SELECT * FROM robots FOR UPDATE
 *</code>
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, forUpdate) {

	zval *sqlQuery_param = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

		if (Z_TYPE_P(sqlQuery_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		sqlQuery = sqlQuery_param;



	ZEPHIR_CONCAT_VS(return_value, sqlQuery, " FOR UPDATE");
	RETURN_MM();

}

/**
 * Returns a SQL modified with a LOCK IN SHARE MODE clause
 *
 *<code>
 * $sql = $dialect->sharedLock('SELECT * FROM robots');
 * echo $sql; // SELECT * FROM robots LOCK IN SHARE MODE
 *</code>
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, sharedLock) {

	zval *sqlQuery_param = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

		if (Z_TYPE_P(sqlQuery_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		sqlQuery = sqlQuery_param;



	ZEPHIR_CONCAT_VS(return_value, sqlQuery, " LOCK IN SHARE MODE");
	RETURN_MM();

}

/**
 * Gets a list of columns with escaped identifiers
 *
 *<code>
 * echo $dialect->getColumnList(array('column1', 'column'));
 *</code>
 *
 * @param	array columnList
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, getColumnList) {

	HashTable *_1;
	HashPosition _0;
	zval *columnList, *strList, *escapeChar, *column = NULL, **_2, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &columnList);



	ZEPHIR_INIT_VAR(strList);
	array_init(strList);
	escapeChar = zephir_fetch_nproperty_this(this_ptr, SL("_escapeChar"), PH_NOISY_CC);
	zephir_is_iterable(columnList, &_1, &_0, 0, 0);
	for (
		; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		; zend_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(column, _2);
		ZEPHIR_INIT_LNVAR(_3);
		ZEPHIR_CONCAT_VVV(_3, escapeChar, column, escapeChar);
		zephir_array_append(&strList, _3, PH_SEPARATE);
	}
	zephir_fast_join_str(return_value, SL(", "), strList TSRMLS_CC);
	RETURN_MM();

}

/**
 * Transforms an intermediate representation for a expression into a database system valid expression
 *
 * @param array expression
 * @param string escapeChar
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, getSqlExpression) {

	zend_function *_10 = NULL, *_14 = NULL;
	HashTable *_7, *_12;
	HashPosition _6, _11;
	zval *escapeChar = NULL, *_1 = NULL;
	zval *expression, *escapeChar_param = NULL, *type, *domain, *operator, *left = NULL, *right = NULL, *name = NULL, *sqlItems, *escapedName = NULL, *sqlArguments, *arguments, *argument = NULL, *item = NULL, *_0, *_2, *_3, *_4, *_5 = NULL, **_8, *_9 = NULL, **_13, *_15, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &expression, &escapeChar_param);

	if (!escapeChar_param || Z_TYPE_P(escapeChar_param) == IS_NULL) {
		ZEPHIR_INIT_VAR(escapeChar);
		ZVAL_EMPTY_STRING(escapeChar);
	} else {
		zephir_get_strval(escapeChar, escapeChar_param);
	}


	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		if (ZEPHIR_IS_STRING(escapeChar, "")) {
			ZEPHIR_OBS_VAR(_0);
			zephir_read_property_this(&_0, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
			zephir_get_strval(_1, _0);
			ZEPHIR_CPY_WRT(escapeChar, _1);
		}
	}
	if ((Z_TYPE_P(expression) != IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid SQL expression");
		return;
	}
	if (!(zephir_array_isset_string_fetch(&type, expression, SS("type"), 1 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid SQL expression");
		return;
	}
	if (ZEPHIR_IS_STRING(type, "qualified")) {
		ZEPHIR_OBS_VAR(name);
		zephir_array_fetch_string(&name, expression, SL("name"), PH_NOISY TSRMLS_CC);
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_INIT_VAR(escapedName);
			ZEPHIR_CONCAT_VVV(escapedName, escapeChar, name, escapeChar);
		} else {
			ZEPHIR_CPY_WRT(escapedName, name);
		}
		if (zephir_array_isset_string_fetch(&domain, expression, SS("domain"), 1 TSRMLS_CC)) {
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VVVSV(return_value, escapeChar, domain, escapeChar, ".", escapedName);
				RETURN_MM();
			} else {
				ZEPHIR_CONCAT_VSV(return_value, domain, ".", escapedName);
				RETURN_MM();
			}
		}
		RETURN_CCTOR(escapedName);
	}
	if (ZEPHIR_IS_STRING(type, "literal")) {
		zephir_array_fetch_string(&_2, expression, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	if (ZEPHIR_IS_STRING(type, "binary-op")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_VAR(left);
		zephir_call_method_p2(left, this_ptr, "getsqlexpression", _2, escapeChar);
		zephir_array_fetch_string(&_3, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_VAR(right);
		zephir_call_method_p2(right, this_ptr, "getsqlexpression", _3, escapeChar);
		zephir_array_fetch_string(&_4, expression, SL("op"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CONCAT_VSVSV(return_value, left, " ", _4, " ", right);
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "unary-op")) {
		zephir_array_fetch_string(&operator, expression, SL("op"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_OBS_NVAR(left);
		if (zephir_array_isset_string_fetch(&left, expression, SS("left"), 0 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(_5);
			zephir_call_method_p2(_5, this_ptr, "getsqlexpression", left, escapeChar);
			ZEPHIR_CONCAT_VV(return_value, _5, operator);
			RETURN_MM();
		}
		ZEPHIR_OBS_NVAR(right);
		if (zephir_array_isset_string_fetch(&right, expression, SS("right"), 0 TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(_5);
			zephir_call_method_p2(_5, this_ptr, "getsqlexpression", right, escapeChar);
			ZEPHIR_CONCAT_VV(return_value, _5, operator);
			RETURN_MM();
		}
	}
	if (ZEPHIR_IS_STRING(type, "placeholder")) {
		zephir_array_fetch_string(&_2, expression, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	if (ZEPHIR_IS_STRING(type, "parentheses")) {
		ZEPHIR_INIT_NVAR(_5);
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_call_method_p2(_5, this_ptr, "getsqlexpression", _2, escapeChar);
		ZEPHIR_CONCAT_SVS(return_value, "(", _5, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "functionCall")) {
		ZEPHIR_OBS_NVAR(name);
		zephir_array_fetch_string(&name, expression, SL("name"), PH_NOISY TSRMLS_CC);
		ZEPHIR_INIT_VAR(sqlArguments);
		array_init(sqlArguments);
		if (zephir_array_isset_string_fetch(&arguments, expression, SS("arguments"), 1 TSRMLS_CC)) {
			zephir_is_iterable(arguments, &_7, &_6, 0, 0);
			for (
				; zend_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
				; zend_hash_move_forward_ex(_7, &_6)
			) {
				ZEPHIR_GET_HVALUE(argument, _8);
				ZEPHIR_INIT_NVAR(_9);
				zephir_call_method_p2_cache(_9, this_ptr, "getsqlexpression", &_10, argument, escapeChar);
				zephir_array_append(&sqlArguments, _9, PH_SEPARATE);
			}
			ZEPHIR_INIT_NVAR(_9);
			zephir_fast_join_str(_9, SL(", "), sqlArguments TSRMLS_CC);
			ZEPHIR_CONCAT_VSVS(return_value, name, "(", _9, ")");
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_VS(return_value, name, "()");
			RETURN_MM();
		}
	}
	if (ZEPHIR_IS_STRING(type, "list")) {
		ZEPHIR_INIT_VAR(sqlItems);
		array_init(sqlItems);
		zephir_array_fetch_long(&_2, expression, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_is_iterable(_2, &_12, &_11, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_12, (void**) &_13, &_11) == SUCCESS
			; zend_hash_move_forward_ex(_12, &_11)
		) {
			ZEPHIR_GET_HVALUE(item, _13);
			ZEPHIR_INIT_NVAR(_5);
			zephir_call_method_p2_cache(_5, this_ptr, "getsqlexpression", &_14, item, escapeChar);
			zephir_array_append(&sqlItems, _5, PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_5);
		zephir_fast_join_str(_5, SL(", "), sqlItems TSRMLS_CC);
		ZEPHIR_CONCAT_SVS(return_value, "(", _5, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "all")) {
		RETURN_MM_STRING("*", 1);
	}
	if (ZEPHIR_IS_STRING(type, "cast")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_NVAR(left);
		zephir_call_method_p2(left, this_ptr, "getsqlexpression", _2, escapeChar);
		zephir_array_fetch_string(&_3, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_NVAR(right);
		zephir_call_method_p2(right, this_ptr, "getsqlexpression", _3, escapeChar);
		ZEPHIR_CONCAT_SVSVS(return_value, "CAST(", left, " AS ", right, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "convert")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_NVAR(left);
		zephir_call_method_p2(left, this_ptr, "getsqlexpression", _2, escapeChar);
		zephir_array_fetch_string(&_3, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_INIT_NVAR(right);
		zephir_call_method_p2(right, this_ptr, "getsqlexpression", _3, escapeChar);
		ZEPHIR_CONCAT_SVSVS(return_value, "CONVERT(", left, " USING ", right, ")");
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_15);
	object_init_ex(_15, phalcon_db_exception_ce);
	ZEPHIR_INIT_VAR(_16);
	ZEPHIR_CONCAT_SVS(_16, "Invalid SQL expression type '", type, "'");
	zephir_call_method_p1_noret(_15, "__construct", _16);
	zephir_throw_exception(_15 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Transform an intermediate representation for a schema/table into a database system valid expression
 *
 * @param array table
 * @param string escapeChar
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, getSqlTable) {

	zval *escapeChar = NULL, *_1 = NULL;
	zval *table, *escapeChar_param = NULL, *sqlTable = NULL, *sqlSchema = NULL, *aliasName, *sqlTableAlias = NULL, *schemaName, *tableName, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table, &escapeChar_param);

	if (!escapeChar_param || Z_TYPE_P(escapeChar_param) == IS_NULL) {
		ZEPHIR_INIT_VAR(escapeChar);
		ZVAL_EMPTY_STRING(escapeChar);
	} else {
		zephir_get_strval(escapeChar, escapeChar_param);
	}


	if (ZEPHIR_IS_STRING(escapeChar, "")) {
		ZEPHIR_OBS_VAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
		zephir_get_strval(_1, _0);
		ZEPHIR_CPY_WRT(escapeChar, _1);
	}
	if ((Z_TYPE_P(table) == IS_ARRAY)) {
		zephir_array_fetch_long(&tableName, table, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_INIT_VAR(sqlTable);
			ZEPHIR_CONCAT_VVV(sqlTable, escapeChar, tableName, escapeChar);
		} else {
			ZEPHIR_CPY_WRT(sqlTable, tableName);
		}
		zephir_array_fetch_long(&schemaName, table, 1, PH_NOISY | PH_READONLY TSRMLS_CC);
		if ((Z_TYPE_P(schemaName) != IS_ARRAY)) {
			ZEPHIR_INIT_VAR(sqlSchema);
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VVVSV(sqlSchema, escapeChar, schemaName, escapeChar, ".", sqlTable);
			} else {
				ZEPHIR_CONCAT_VSV(sqlSchema, schemaName, ".", sqlTable);
			}
		} else {
			ZEPHIR_CPY_WRT(sqlSchema, sqlTable);
		}
		if (zephir_array_isset_long_fetch(&aliasName, table, 2, 1 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(sqlTableAlias);
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VSVVV(sqlTableAlias, sqlSchema, " AS ", escapeChar, aliasName, escapeChar);
			} else {
				ZEPHIR_CONCAT_VSV(sqlTableAlias, sqlSchema, " AS ", aliasName);
			}
		} else {
			ZEPHIR_CPY_WRT(sqlTableAlias, sqlSchema);
		}
		RETURN_CCTOR(sqlTableAlias);
	}
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		ZEPHIR_CONCAT_VVV(return_value, escapeChar, table, escapeChar);
		RETURN_MM();
	}
	RETURN_CCTOR(table);

}

/**
 * Builds a SELECT statement
 *
 * @param array definition
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, select) {

	zend_function *_3 = NULL, *_8 = NULL, *_13 = NULL, *_18 = NULL, *_25 = NULL, *_30 = NULL;
	HashTable *_1, *_5, *_10, *_16, *_23, *_28;
	HashPosition _0, _4, _9, _15, _22, _27;
	zval *definition, *tables, *columns = NULL, *escapeChar, *columnItem, *column = NULL, *selectedColumns, *columnSql = NULL, *columnDomainSql = NULL, *columnAlias, *selectedTables, *sqlJoin = NULL, *joinExpressions = NULL, *joinCondition = NULL, *joinConditionsArray, *tablesSql = NULL, *columnDomain, *columnAliasSql = NULL, *columnsSql = NULL, *table = NULL, *sql, *joins, *join = NULL, *sqlTable = NULL, *whereConditions, *groupFields, *groupField = NULL, *groupItems, *havingConditions, *orderFields, *orderItem = NULL, *orderItems, *orderSqlItem = NULL, *sqlOrderType, *orderSqlItemType = NULL, *limitValue, *number, *offset, **_2, **_6, *_7 = NULL, **_11, *_12, *_14, **_17, *_19 = NULL, *_20 = NULL, *_21 = NULL, **_24, *_26 = NULL, **_29, *_31;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &definition);



	if ((Z_TYPE_P(definition) == IS_ARRAY)) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "Invalid SELECT definition");
		return;
	}
	if (!(zephir_array_isset_string_fetch(&tables, definition, SS("tables"), 1 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The index 'tables' is required in the definition array");
		return;
	}
	ZEPHIR_OBS_VAR(columns);
	if (!(zephir_array_isset_string_fetch(&columns, definition, SS("columns"), 0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_STR(phalcon_db_exception_ce, "The index 'columns' is required in the definition array");
		return;
	}
	ZEPHIR_INIT_VAR(escapeChar);
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		zephir_read_property_this(&escapeChar, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
	} else {
		ZVAL_NULL(escapeChar);
	}
	ZEPHIR_OBS_NVAR(columns);
	zephir_array_fetch_string(&columns, definition, SL("columns"), PH_NOISY TSRMLS_CC);
	if ((Z_TYPE_P(columns) == IS_ARRAY)) {
		ZEPHIR_INIT_VAR(selectedColumns);
		array_init(selectedColumns);
		zephir_is_iterable(columns, &_1, &_0, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
			; zend_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(column, _2);
			zephir_array_fetch_long(&columnItem, column, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			if ((Z_TYPE_P(columnItem) == IS_ARRAY)) {
				ZEPHIR_INIT_NVAR(columnSql);
				zephir_call_method_p2_cache(columnSql, this_ptr, "getsqlexpression", &_3, columnItem, escapeChar);
			} else {
				if (ZEPHIR_IS_STRING(columnItem, "*")) {
					ZEPHIR_CPY_WRT(columnSql, columnItem);
				} else {
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_INIT_NVAR(columnSql);
						ZEPHIR_CONCAT_VVV(columnSql, escapeChar, columnItem, escapeChar);
					} else {
						ZEPHIR_CPY_WRT(columnSql, columnItem);
					}
				}
			}
			if (zephir_array_isset_long_fetch(&columnDomain, column, 1, 1 TSRMLS_CC)) {
				if (zephir_is_true(columnDomain)) {
					ZEPHIR_INIT_NVAR(columnDomainSql);
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_CONCAT_VVVSV(columnDomainSql, escapeChar, columnDomain, escapeChar, ".", columnSql);
					} else {
						ZEPHIR_CONCAT_VSV(columnDomainSql, columnDomain, ".", columnSql);
					}
				} else {
					ZEPHIR_CPY_WRT(columnDomainSql, columnSql);
				}
			} else {
				ZEPHIR_CPY_WRT(columnDomainSql, columnSql);
			}
			if (zephir_array_isset_long_fetch(&columnAlias, column, 2, 1 TSRMLS_CC)) {
				if (zephir_is_true(columnAlias)) {
					ZEPHIR_INIT_NVAR(columnAliasSql);
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_CONCAT_VSVVV(columnAliasSql, columnDomainSql, " AS ", escapeChar, columnAlias, escapeChar);
					} else {
						ZEPHIR_CONCAT_VSV(columnAliasSql, columnDomainSql, " AS ", columnAlias);
					}
				} else {
					ZEPHIR_CPY_WRT(columnAliasSql, columnDomainSql);
				}
			} else {
				ZEPHIR_CPY_WRT(columnAliasSql, columnDomainSql);
			}
			zephir_array_append(&selectedColumns, columnAliasSql, PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(columnsSql);
		zephir_fast_join_str(columnsSql, SL(", "), selectedColumns TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(columnsSql, columns);
	}
	if ((Z_TYPE_P(tables) == IS_ARRAY)) {
		ZEPHIR_INIT_VAR(selectedTables);
		array_init(selectedTables);
		zephir_is_iterable(tables, &_5, &_4, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
			; zend_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HVALUE(table, _6);
			ZEPHIR_INIT_NVAR(_7);
			zephir_call_method_p2_cache(_7, this_ptr, "getsqltable", &_8, table, escapeChar);
			zephir_array_append(&selectedTables, _7, PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(tablesSql);
		zephir_fast_join_str(tablesSql, SL(", "), selectedTables TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(tablesSql, tables);
	}
	ZEPHIR_INIT_VAR(sql);
	ZEPHIR_CONCAT_SVSV(sql, "SELECT ", columnsSql, " FROM ", tablesSql);
	if (zephir_array_isset_string_fetch(&joins, definition, SS("joins"), 1 TSRMLS_CC)) {
		zephir_is_iterable(joins, &_10, &_9, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
			; zend_hash_move_forward_ex(_10, &_9)
		) {
			ZEPHIR_GET_HVALUE(join, _11);
			zephir_array_fetch_string(&_12, join, SL("source"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(sqlTable);
			zephir_call_method_p2_cache(sqlTable, this_ptr, "getsqltable", &_13, _12, escapeChar);
			zephir_array_append(&selectedTables, sqlTable, PH_SEPARATE);
			zephir_array_fetch_string(&_14, join, SL("type"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(sqlJoin);
			ZEPHIR_CONCAT_SVSV(sqlJoin, " ", _14, " JOIN ", sqlTable);
			if (zephir_array_isset_string_fetch(&joinConditionsArray, join, SS("conditions"), 1 TSRMLS_CC)) {
				if (zephir_fast_count_int(joinConditionsArray TSRMLS_CC)) {
					ZEPHIR_INIT_NVAR(joinExpressions);
					array_init(joinExpressions);
					zephir_is_iterable(joinConditionsArray, &_16, &_15, 0, 0);
					for (
						; zend_hash_get_current_data_ex(_16, (void**) &_17, &_15) == SUCCESS
						; zend_hash_move_forward_ex(_16, &_15)
					) {
						ZEPHIR_GET_HVALUE(joinCondition, _17);
						ZEPHIR_INIT_NVAR(_7);
						zephir_call_method_p2_cache(_7, this_ptr, "getsqlexpression", &_18, joinCondition, escapeChar);
						zephir_array_append(&joinExpressions, _7, PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_19);
					zephir_fast_join_str(_19, SL(" AND "), joinExpressions TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_20);
					ZEPHIR_CONCAT_SVS(_20, " ON ", _19, " ");
					zephir_concat_self(&sqlJoin, _20 TSRMLS_CC);
				}
			}
			zephir_concat_self(&sql, sqlJoin TSRMLS_CC);
		}
	}
	if (zephir_array_isset_string_fetch(&whereConditions, definition, SS("where"), 1 TSRMLS_CC)) {
		if ((Z_TYPE_P(whereConditions) == IS_ARRAY)) {
			ZEPHIR_INIT_NVAR(_7);
			zephir_call_method_p2(_7, this_ptr, "getsqlexpression", whereConditions, escapeChar);
			ZEPHIR_INIT_LNVAR(_20);
			ZEPHIR_CONCAT_SV(_20, " WHERE ", _7);
			zephir_concat_self(&sql, _20 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_VAR(_21);
			ZEPHIR_CONCAT_SV(_21, " WHERE ", whereConditions);
			zephir_concat_self(&sql, _21 TSRMLS_CC);
		}
	}
	if (zephir_array_isset_string_fetch(&groupFields, definition, SS("group"), 1 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(groupItems);
		array_init(groupItems);
		zephir_is_iterable(groupFields, &_23, &_22, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_23, (void**) &_24, &_22) == SUCCESS
			; zend_hash_move_forward_ex(_23, &_22)
		) {
			ZEPHIR_GET_HVALUE(groupField, _24);
			ZEPHIR_INIT_NVAR(_7);
			zephir_call_method_p2_cache(_7, this_ptr, "getsqlexpression", &_25, groupField, escapeChar);
			zephir_array_append(&groupItems, _7, PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_7);
		zephir_fast_join_str(_7, SL(", "), groupItems TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_21);
		ZEPHIR_CONCAT_SV(_21, " GROUP BY ", _7);
		zephir_concat_self(&sql, _21 TSRMLS_CC);
		if (zephir_array_isset_string_fetch(&havingConditions, definition, SS("having"), 1 TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(_19);
			zephir_call_method_p2(_19, this_ptr, "getsqlexpression", havingConditions, escapeChar);
			ZEPHIR_INIT_VAR(_26);
			ZEPHIR_CONCAT_SV(_26, " HAVING ", _19);
			zephir_concat_self(&sql, _26 TSRMLS_CC);
		}
	}
	if (zephir_array_isset_string_fetch(&orderFields, definition, SS("order"), 1 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(orderItems);
		array_init(orderItems);
		zephir_is_iterable(orderFields, &_28, &_27, 0, 0);
		for (
			; zend_hash_get_current_data_ex(_28, (void**) &_29, &_27) == SUCCESS
			; zend_hash_move_forward_ex(_28, &_27)
		) {
			ZEPHIR_GET_HVALUE(orderItem, _29);
			zephir_array_fetch_long(&_12, orderItem, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(orderSqlItem);
			zephir_call_method_p2_cache(orderSqlItem, this_ptr, "getsqlexpression", &_30, _12, escapeChar);
			if (zephir_array_isset_long_fetch(&sqlOrderType, orderItem, 1, 1 TSRMLS_CC)) {
				ZEPHIR_INIT_NVAR(orderSqlItemType);
				ZEPHIR_CONCAT_VSV(orderSqlItemType, orderSqlItem, " ", sqlOrderType);
			} else {
				ZEPHIR_CPY_WRT(orderSqlItemType, orderSqlItem);
			}
			zephir_array_append(&orderItems, orderSqlItemType, PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_7);
		zephir_fast_join_str(_7, SL(", "), orderItems TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_21);
		ZEPHIR_CONCAT_SV(_21, " ORDER BY ", _7);
		zephir_concat_self(&sql, _21 TSRMLS_CC);
	}
	if (zephir_array_isset_string_fetch(&limitValue, definition, SS("limit"), 1 TSRMLS_CC)) {
		if ((Z_TYPE_P(limitValue) == IS_ARRAY)) {
			zephir_array_fetch_string(&number, limitValue, SL("number"), PH_NOISY | PH_READONLY TSRMLS_CC);
			if (zephir_array_isset_string_fetch(&offset, limitValue, SS("offset"), 1 TSRMLS_CC)) {
				ZEPHIR_INIT_LNVAR(_26);
				ZEPHIR_CONCAT_SVSV(_26, " LIMIT ", number, " OFFSET ", offset);
				zephir_concat_self(&sql, _26 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_VAR(_31);
				ZEPHIR_CONCAT_SV(_31, " LIMIT ", number);
				zephir_concat_self(&sql, _31 TSRMLS_CC);
			}
		} else {
			ZEPHIR_INIT_LNVAR(_21);
			ZEPHIR_CONCAT_SV(_21, " LIMIT ", limitValue);
			zephir_concat_self(&sql, _21 TSRMLS_CC);
		}
	}
	RETURN_CCTOR(sql);

}

/**
 * Checks whether the platform supports savepoints
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Dialect, supportsSavepoints) {


	RETURN_BOOL(1);

}

/**
 * Checks whether the platform supports releasing savepoints.
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Dialect, supportsReleaseSavepoints) {

	ZEPHIR_MM_GROW();

	zephir_call_method(return_value, this_ptr, "supportssavepoints");
	RETURN_MM();

}

/**
 * Generate SQL to create a new savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, createSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

		if (Z_TYPE_P(name_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		name = name_param;



	ZEPHIR_CONCAT_SV(return_value, "SAVEPOINT ", name);
	RETURN_MM();

}

/**
 * Generate SQL to release a savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, releaseSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

		if (Z_TYPE_P(name_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		name = name_param;



	ZEPHIR_CONCAT_SV(return_value, "RELEASE SAVEPOINT ", name);
	RETURN_MM();

}

/**
 * Generate SQL to rollback a savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, rollbackSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

		if (Z_TYPE_P(name_param) != IS_STRING) {
				zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
				RETURN_MM_NULL();
		}

		name = name_param;



	ZEPHIR_CONCAT_SV(return_value, "ROLLBACK TO SAVEPOINT ", name);
	RETURN_MM();

}

