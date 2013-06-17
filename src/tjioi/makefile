JUDGE_NAME=tjioi
GRADER_DIR=../../bin

all:
	cc -I libsandbox/src -lsandbox -lrt $(JUDGE_NAME).c -o $(JUDGE_NAME) libsandbox/libsandbox.a

install:
	mkdir -p $(GRADER_DIR)/judges
	cp $(JUDGE_NAME) $(GRADER_DIR)/judges

