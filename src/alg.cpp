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
  std::string res = "";

  for (int i = 0; i < (int)inf.size(); i++) {

    if (isdigit(inf[i])) {
      while (i < (int)inf.size() && isdigit(inf[i])) {
        res += inf[i];
        i++;
      }
      res += ' ';
      i--;
    }

    else if (inf[i] == '(') {
      st.push(inf[i]);
    }

    else if (inf[i] == ')') {
      while (!st.isEmpty() && st.top() != '(') {
        res += st.top();
        res += ' ';
        st.pop();
      }
      st.pop();
    }

    else {
      while (!st.isEmpty() && prior(st.top()) >= prior(inf[i])) {
        res += st.top();
        res += ' ';
        st.pop();
      }
      st.push(inf[i]);
    }
  }

  while (!st.isEmpty()) {
    res += st.top();
    res += ' ';
    st.pop();
  }

  return res;
}

int eval(const std::string& pref) {
  TStack<int, 100> st;

  const std::string& post = pref;

  for (int i = 0; i < (int)post.size(); i++) {

    if (isdigit(post[i])) {
      int num = 0;

      while (i < (int)post.size() && isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        i++;
      }

      st.push(num);
      i--;
    }

    else if (post[i] == '+' || post[i] == '-' ||
             post[i] == '*' || post[i] == '/') {

      int b = st.top(); st.pop();
      int a = st.top(); st.pop();

      int r = 0;

      if (post[i] == '+') r = a + b;
      else if (post[i] == '-') r = a - b;
      else if (post[i] == '*') r = a * b;
      else if (post[i] == '/') r = a / b;

      st.push(r);
    }
  }

  return st.top();
}
