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

TEST_CASE("GitHub GraphQL", "[github]") {
  SECTION("Read GitHub's schema") {
    FILE *fp = fopen("./feature-tests/github_schema_clean.graphql", "r");
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
