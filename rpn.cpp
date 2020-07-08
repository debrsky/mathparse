#include <iostream>
#include <string>

// http://e-maxx.ru/algo/expressions_parsing
// https://algolist.manual.ru/syntax/revpn.php

#define MAX_OPERATORS_STACK 1000

std::string rpn_result_string = "";

bool is_delim(char c);
bool is_operator(char c);
int priority (std::string token);


std::string stack[MAX_OPERATORS_STACK];
int stack_pos = 0;

bool stack_is_empty()
{
  return stack_pos == 0;
}

void stack_push(std::string value)
{
  if (stack_pos > MAX_OPERATORS_STACK) throw "Переполнение стека";
  stack[stack_pos++] = value;
}

std::string stack_pop()
{
  if (stack_pos - 1 < 0) throw "Стек пуст";
  return stack[--stack_pos];
}

std::string stack_peek()
{
  if (stack_pos - 1 < 0) throw "Стек пуст";
  return stack[stack_pos - 1];
}


void output_token (std::string token)
{
  if (!rpn_result_string.empty()) rpn_result_string = rpn_result_string + " ";
  rpn_result_string = rpn_result_string + token;
}

void show_token(std::string token)
{
  if (token.empty()) token = "<пусто>";

  if (!is_operator(token.at(0))) {
    output_token(token);
    return;
  }

  // Токен является оператором

  // Если стек пуст или оператор "открывающая скобка (", то оператор записывается в стек
  if (stack_is_empty() || token == "(") {
    stack_push(token);
    return;
  }

  // Если оператор "Закрывающая скобка )", то извлекать из стека операторы, пока не встретится "Открывающая скобка"
  if (token == ")") {
    std::string stoken = stack_pop();
    while (stoken != "(") {
      output_token (stoken);
      
      if (stack_is_empty()) throw "Ошибка расстановки скобок";

      stoken = stack_pop();
    }
    return;
  }

  // стек не пуст и токен является обычным оператором (не скобкой)
  int current_priority = priority(token);
  while (!stack_is_empty()) {
    std::string stoken = stack_peek();

    if (priority(stoken) < current_priority) break;

    stack_pop();
    output_token(stoken);
  }

  stack_push(token);
}

bool is_delim(char c)
{
  return c == ' ';
}


bool is_operator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

int priority (std::string token)
{
  if (token == "(" || token == ")") return 0;
  if (token == "+" || token == "-") return 10;
  if (token == "*" || token == "/") return 20;

  throw "Неизвестный оператор";
}

std::string math_rpn(std::string str)
{
  if (str.empty()) return "";

  rpn_result_string = "";
  stack_pos = 0;

  std::string token = "";
  for (std::string::iterator chr = str.begin(); chr != str.end(); ++chr) {
    if (is_delim(*chr)) {
      if (token.empty()) continue;

      show_token(token);
      token = "";
      continue;
    }

    if (is_operator(*chr)) {
      if (!token.empty()) show_token(token);
      token = *chr;
      show_token(token);
      token = "";
      continue;
    }

    token = token + *chr;

  }
  if (!token.empty()) show_token(token);

  while (!stack_is_empty()) {
    std::string token = stack_pop();
    output_token(token);
  }

  return rpn_result_string;
}
