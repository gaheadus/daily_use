# 1.Ԫ�ַ�,Metacharacter
&emsp;&emsp;[����Ԫ�ַ�](#����Ԫ�ַ�)  
&emsp;&emsp;[Ԫ�ַ��ķ���](#Ԫ�ַ��ķ���)  
&emsp;&emsp;[�����ַ�](#�����ַ�)

## ����Ԫ�ַ�
|  **Character classes**  |  **�ַ������ַ���**  |  **��ע**  |
| --- | --- | --- |
| **.**                 |  any single character except newline  |  |
| \w \d \s              |  word, digit, whitespace    |  |
| \W \D \S              |  not word, digit, whitespace  |  |
| [abc]                 |  any of a, b, or c                           |    A single character of: a, b, or c  |
| [^abc]                |  not a, b, or c                                |    A single character except: a, b, or c  |
| [a-g]                 |  character between a \& g              |    Any single character in the range a-g  |
| [a-zA-Z]              |                                              |    Any single character in the range a-z or A-Z  |
| **Anchors**           |   **ê�㣬��λ��**    |  |
| ^                     |  matches the position at the start of the line  |  |
| $                     |  matches the position at the end of the line  |  |
| \<                    |  matches the position at the start of a word  |  |
| \>                    |  matches the position at the end of a word  |  |
| \b                    |  any word boundary  |  |
| \B                    |  not-word boundary  |  |
| **Escaped characters** |   **ת���ַ�**  |  |
| \\. \\* \\\           |  escaped special characters  |  |
| \t \n \r              |  tab, linefeed, carriage return  |  |
| \s                    |  any whitespace character  |  |
| \S                    |  any non-whitespace character  |  |
| \d                    |  any digit  |  |
| \D                    |  any non-digit  |  |
| \w                    |  any word character (letter, number, underscore)  |  |
| \W                    |  any non-word character  |  |
| \b                    |  any word boundary  |  |
| \u00A9                |  unicode escaped ?
| **Groups \& Lookaround** |    **���� \& ����**  |  |
| (abc)                 |  capture group                              |   (...)  Capture everything enclosed  |
| \1                    |  backreference to group #1          |   �������÷��飬��\1��\2��\3  |
| (?:abc)               |  non-capturing group  |  |
| (?=)                  |  positive lookahead  |  |
| (?!)                  |  negative lookahead  |  |
| **Quantifiers \& Alternation** |    **���� \& ��ѡ**  |  |
| a?                    |  zero or one of a  |  |
| a\*                   |  zero or more of a  |  |
| a+                    |  one or more of a  |  |
| a{3}                  |  exactly 3 of a  |  |
| a{3,6}                |  between 3 and 6 of a  |  |
| a{3,}                 |  3 or more of a  |  |
| a+?  a{2,}?           |  match as few as possible  |  |
| ab\|cd                |  match ab or cd                         |    (a\|b)  a or b |

Ҫ�ʵ��ο�Ӣ��ԭ�ģ���Ϊ��ʱ�����ķ��벻��̫��׼��

**��ע1��** \s - space,  \w - word ,  \d - digital , \r - return , \n - new line , \t - tab , \b - boundary
**\w** : ���е�����Сд **��ĸ�����֡��»���** ����[a-zA-Z0-9\_]��ͬ��
**\s** : ���е��� **�հ��ַ�** �� **�����ո��Ʊ��س������е��ַ�** ("\t\r\n")��


## Ԫ�ַ��ķ���
�����ַ�����ʾ�����壬�����ࣺ  
1. \d��\D��\w��\s��.�� **��ʾ�ַ�** ��  
2. ?\*+{m,n}�� **��ʾ����** ��ע:?���ڲ�ͬ�ط����岻һ��,�����ַ����ʾ����,�����������ʾ����ƥ�䣻  
3. ^��$��\b��\<��\>�� **��ʾλ��** ������(������)Ҳ����ƥ��ĳ��λ�á�  
���ַ��������࣬�����ࣺ���ַ���Ԫ�ַ�����.\*+���Ͷ��ַ���Ԫ�ַ�����\b\w\[abc\]\(?:\)��

&nbsp;

## �����ַ�
\w�����ʾ��ĸ�����»���֮�⣬Ҳ���Ա�ʾ�������֣����������Է��š�  
��ô�����ƥ�䵥�����֣���Unicode���뻷����ʹ�õ�������ʽ��ƥ��Unicode�ַ����л����������ַ���ʹ��[\u4e00-\u9fff]��[\u{4e00}-\u{9fff}]����ͬ�Ĺ��߱�ʾ��ʽ���ܲ�һ�����ο�������ָ��.���ɡ�--��¼b �� �õ�������ʽ�������ַ�  
��ע��[^\u4e00-\u9fff]ƥ��Ǻ��֣�[a-zA-Z0-9_\u4e00-\u9fff]ƥ�������ַ�����ĸ�����֡��»��ߡ�

ƥ�����ĺ���:[\u4e00-\u9fff]��  
ƥ�����ı�����:[\u3002\uff1b\uff0c\uff1a\u201c\u201d\uff08\uff09\u3001\uff1f\u300a\u300b]���ñ��ʽ����ʶ�� �� �� �� �� �� ���� �� �� �� �� ���ȱ����š�  
ƥ��˫�ֽ��ַ�:[^\x00-\xff]��

**notepad++ƥ������**  
ͨ��������ʽƥ�����Ŀ�������Unicode���ص㣬ʹ��[\u4e00-\u9fff]ƥ�䡣����Notepad++�в�������ʹ�á�  
��������ǣ����Ƚ�����ת����Unicode���˵�->��ʽ->ת��ΪUTF-8�������ת������ƥ�������Ȼ��ʹ��[\x{4e00}-\x{9fff}]�Ϳ���ʵ��ƥ�������ˡ�  
����˵����[һ-��]�����к��֣�[һ-����-��]�����к��ּӱ�㡣
