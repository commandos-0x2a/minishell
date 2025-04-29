from fpdf import FPDF
 
 
files = [
	"Makefile",
	"include/minishell.h",
	"src/wait_children.c",
	"src/bonus/execute_simple_command.c",
	"src/bonus/expand_wildcard.c",
	"src/bonus/utils.c",
	"src/bonus/execute_complex_command.c",
	"src/bonus/expand_tokens.c",
	"src/bonus/subshell.c",
	"src/bonus/flow_control.c",
	"src/pipeline_control.c",
	"src/expand_str.c",
	"src/redirection_handler.c",
	"src/mandatory/execute_simple_command.c",
	"src/mandatory/utils.c",
	"src/mandatory/execute_complex_command.c",
	"src/mandatory/expand_tokens.c",
	"src/utils/print_error.c",
	"src/utils/dptr.c",
	"src/utils/ft_getenv.c",
	"src/utils/get_full_path.c",
	"src/utils/tty.c",
	"src/utils/ft_list.c",
	"src/builtins/builtins.c",
	"src/builtins/exit.c",
	"src/builtins/unset.c",
	"src/builtins/env.c",
	"src/builtins/pwd.c",
	"src/builtins/export.c",
	"src/builtins/cd.c",
	"src/builtins/echo.c",
	"src/check_syntax.c",
	"src/expand_env.c",
	"src/main.c",
	"src/get_argv.c",
	"src/heredoc.c",
	"src/tokenizer.c",
	"src/expand_line.c",
	"src/signals.c",
]

def clean_text(text:str):
    return text.encode('latin-1', 'ignore').decode('latin-1')

def text_to_pdf(output_pdf_path):
	# Create instance of FPDF class
	pdf = FPDF()
	pdf.set_auto_page_break(auto=True, margin=10)
	pdf.add_font("Andale Mono", "", "/System/Library/Fonts/Supplemental/Andale Mono.ttf")
	pdf.set_font("Andale Mono", size=10)
	pdf.add_page()

	for file in files:
		with open(file, "r", encoding="utf-8") as f:
			for line in f:
				clean_line = clean_text(line)
				clean_line = clean_line.replace("\t", "    ")
				pdf.multi_cell(0, 0, text=clean_line)
	pdf.output(output_pdf_path)
	print(f"PDF created successfully: {output_pdf_path}")

# Example usage
text_to_pdf("minishell_code.pdf")
