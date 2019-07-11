/**
 * Copyright (c) 2019-present, IBM
 *
 * Build with:
 * c++ -std=gnu++11 -I ./ feature-tests/*.cpp libgraphqlparser.dylib -o test.out
 */
#include <fstream>
#include "Ast.h"
#include "GraphQLParser.h"
#include "c/GraphQLAstToJSON.h"
#include "catch.hpp"

using namespace std;
using namespace facebook::graphql;  // use "parseString" without namespace
using namespace facebook::graphql::ast;

TEST_CASE("ID GraphQL", "[id]") {
  SECTION("Read schema including id scalar") {
    FILE *fp = fopen("./feature-tests/id_schema.graphql", "r");
    const char *error = nullptr;
    auto AST = parseFileWithExperimentalSchemaSupport(fp, &error);

    if (!AST) {
      cerr << "Parser failed with error: " << error << endl;
      free((void *)error);  // NOLINT
    }
    // auto schemaDocument = dynamic_cast<Document *>(AST.get());

    const char *json = graphql_ast_to_json(
        reinterpret_cast<const struct GraphQLAstNode *>(AST.get()));
    puts(json);
    free((void *)json);  // NOLINT

    REQUIRE(AST != nullptr);
  }
}
