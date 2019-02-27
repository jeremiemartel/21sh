# 21sh

env:
  t_dy_tab
  

edition de ligne:
  t_dy_str
  ->historique (fichier)
  ->cmd_r
  ->ctrl a, e
  ->mot/mot
  ->remonter (meme colonne)

AST:
  lexical
  syntaxique
  sémantique
  ?

Jour 0:

t_sh
{
  t_dy_tab *env;
  t_parse   *AST;
  t_prompt  *prompt;
	char			running;
  t_autocomplete		*autocomplete;
}

typedef struct		s_glob
{
	struct termios	term;/////////////////
	struct termios	term_init;
	t_dy_str		*command;
	int				cursor;
	struct winsize	winsize;
}					t_glob;

ft_get_command
  
Jour 1:

 http://pubs.opengroup.org/onlinepubs/9699919799/
