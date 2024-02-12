
class quiz:
    def __init__(self, qid, text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        self.qid = qid
        self.text = text
        self.choice_a = choice_a
        self.choice_b = choice_b
        self.choice_c = choice_c
        self.correct_choice = correct_choice
        self.difficulty = difficulty

    def qid(self):
        return self.qid

    def text(self):
        return self.text

    def choice_a(self):
        return self.choice_a

    def choice_b(self):
        return self.choice_b

    def choice_c(self):
        return self.choice_c

    def correct_choice(self):
        return self.correct_choice

    def difficulty(self):
        return self.difficulty

    def __str__(self):
        return self.qid + " " + self.text + " " + self.choice_a + " " + self.choice_b + " " + self.choice_c + " " + \
               self.correct_choice + " " + self.difficulty
