#include <cstddef>
#include <fstream>
#include <hermes/CompileJS.h>
#include <hermes/hermes.h>
#include <iostream>
#include <jsi/jsi.h>
#include <memory>
#include <sstream>

using namespace facebook;
using namespace facebook::jsi;

static std::string readFile(const char *path) {
  std::ifstream f(path);
  std::stringstream ss;
  ss << f.rdbuf();
  return ss.str();
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: hermes-host <script.js>\n";
    return 1;
  }
  auto rt = facebook::hermes::makeHermesRuntime();

  // inject a print host function so that JS has somewhere to log
  rt->global().setProperty(*rt, "print",
                           Function::createFromHostFunction(
                               *rt, PropNameID::forAscii(*rt, "print"), 1,
                               [](Runtime &rt, const Value &, const Value *args,
                                  size_t count) -> Value {
                                 for (size_t i = 0; i < count; ++i) {
                                   std::cout << args[i].toString(rt).utf8(rt);
                                   if (i + 1 < count)
                                     std::cout << " ";
                                 }
                                 std::cout << "\n";
                                 return Value::undefined();
                               }));
  rt->global().setProperty(*rt, "sum",
                           Function::createFromHostFunction(
                               *rt, PropNameID::forAscii(*rt, "sum"), 2,
                               [](Runtime &rt, const Value &, const Value *args,
                                  size_t count) -> Value {
                                 return Value(args[0].asNumber() +
                                              args[1].asNumber());
                               }));
  auto src = readFile(argv[1]);
  std::string bytecode;
  bool ok = ::hermes::compileJS(src, argv[1], bytecode,
                                true // optimize
  );
  if (!ok) {
    std::cerr << "JS compilation failed \n";
  }
  rt->evaluateJavaScript(std::make_shared<StringBuffer>(bytecode), argv[1]);
  return 0;
}
