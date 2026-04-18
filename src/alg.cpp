// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <cctype>

int prior(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> st;
  std::string out = "";

  for (int i = 0; i < (int)inf.size(); i++) {

    if (isdigit(inf[i])) {
      while (i < (int)inf.size() && isdigit(inf[i])) {
        out += inf[i];
        i++;
      }
      out += ' ';
      i--;
    }

    else if (inf[i] == '(') {
      st.push(inf[i]);
    }

    else if (inf[i] == ')') {
      while (!st.isEmpty() && st.top() != '(') {
        out += st.top();
        out += ' ';
        st.pop();
      }
      st.pop();
    }

    else {
      while (!st.isEmpty() && prior(st.top()) >= prior(inf[i])) {
        out += st.top();
        out += ' ';
        st.pop();
      }
      st.push(inf[i]);
    }
  }

  while (!st.isEmpty()) {
    out += st.top();
    out += ' ';
    st.pop();
  }

  return out;
}

int eval(const std::string& pref) {
  TStack<int, 100> st;

  const std::string& s = pref;

  for (int i = 0; i < (int)s.size(); i++) {

    if (isdigit(s[i])) {
      int num = 0;

      while (i < (int)s.size() && isdigit(s[i])) {
        num = num * 10 + (s[i] - '0');
        i++;
      }

      st.push(num);
      i--;
    }

    else if (s[i] == '+' || s[i] == '-' ||
             s[i] == '*' || s[i] == '/') {

      int b = st.top(); st.pop();
      int a = st.top(); st.pop();

      int res = 0;

      if (s[i] == '+') res = a + b;
      else if (s[i] == '-') res = a - b;
      else if (s[i] == '*') res = a * b;
      else if (s[i] == '/') res = a / b;

      st.push(res);
    }
  }

  return st.top();
}
