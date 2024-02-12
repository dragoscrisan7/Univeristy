
class validator:
    def verify_add(self, cmd):
        try:
            parts = cmd.split(';')
            qid = parts[0]
            text = parts[1]
            choice_a = parts[2]
            choice_b = parts[3]
            choice_c = parts[4]
            correct_choice = parts[5]
            difficulty = parts[6]
        except:
            raise ValueError

        self.verify_id(qid)
        self.verify_text(text)
        self.verify_choice(choice_a)
        self.verify_choice(choice_b)
        self.verify_choice(choice_c)
        self.verify_correct_choice(choice_a, choice_b, choice_c, correct_choice)
        self.verify_difficulty(difficulty)

    def verify_id(self, qid):
        try:
            n = int(qid)
            if n < 0:
                raise
        except:
            raise ValueError

    def verify_text(self, text):
        if len(text) == 0:
            raise ValueError

    def verify_choice(self, choice):
        if len(choice) == 0:
            raise ValueError

    def verify_correct_choice(self, choice_a, choice_b, choice_c, correct_choice):
        if correct_choice != choice_a and correct_choice != choice_b and correct_choice != choice_c:
            raise ValueError
        if choice_a == choice_b or choice_a == choice_c or choice_b == choice_c:
            raise ValueError

    def verify_difficulty(self, difficulty):
        list = ["easy", "medium", "hard"]
        if not difficulty in list:
            raise ValueError

    def verify_create(self, cmd):
        try:
            parts = cmd.split(';')
            difficulty = parts[0]
            number_of_questions = parts[1]
            file = parts[2]
            self.verify_difficulty(difficulty)
            self.verify_number_of_questions(number_of_questions)
            if len(file) < 1:
                raise ValueError
        except:
            raise ValueError


    def verify_number_of_questions(self, number_of_questions):
        try:
            n = int(number_of_questions)
            if n <= 0:
                raise
        except:
            raise ValueError

    def verify_start(self, cmd):
        try:
            self.verify_text(cmd)
        except:
            raise ValueError
