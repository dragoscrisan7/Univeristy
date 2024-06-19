from random import randint


class quiz_services:
    def __init__(self, repo, vali):
        self.repo = repo
        self.vali = vali

    def add(self, cmd):
        self.vali.verify_add(cmd)
        parts = cmd.split(';')
        qid = parts[0]
        self.repo.check_id(qid)
        self.repo.add(cmd)

    def check_questions(self, number_of_questions, difficulty):
        easy = self.repo.list_questions('easy')
        medium = self.repo.list_questions('medium')
        hard = self.repo.list_questions('hard')
        length = len(easy) + len(medium) + len(hard)
        number_of_questions = int(number_of_questions)

        if length < number_of_questions:
            return False
        if difficulty == 'easy':
            if len(easy) < number_of_questions//2 + number_of_questions % 2:
                return False
        if difficulty == 'medium':
            if len(medium) < number_of_questions//2 + number_of_questions % 2:
                return False
        if difficulty == 'hard':
            if len(hard) < number_of_questions//2 + number_of_questions % 2:
                return False

        questions_list = [easy, medium, hard]
        return questions_list

    def create(self, cmd):
        self.vali.verify_create(cmd)
        parts = cmd.split(';')
        difficulty = parts[0]
        number_of_questions = int(parts[1])
        file = parts[2]

        if not self.check_questions(number_of_questions, difficulty):
            raise ValueError
        else:
            questions_list = self.check_questions(number_of_questions, difficulty)

        nr = number_of_questions//2 + number_of_questions % 2
        remainder = number_of_questions - nr
        if difficulty == 'easy':
            p = 0
        elif difficulty == 'hard':
            p = 2
        else:
            p = 1

        q = []
        while nr > 0:
            i = randint(0, len(questions_list[p])-1)
            q.append(questions_list[p][i])
            questions_list[p].pop(i)
            nr -= 1
        while remainder > 0:
            i = randint(0, 2)
            if len(questions_list[i]) != 0:
                question = randint(0, len(questions_list[i])-1)
                q.append(questions_list[i][question])
                questions_list[i].pop(question)
                remainder -= 1

        with open("putancur/"+file, 'w') as f:
            for question in q:
                f.write(f"{question.qid};{question.text};{question.choice_a};{question.choice_b};{question.choice_c};"
                        f"{question.correct_choice};{question.difficulty}\n")

        print("created successfully")

    def start(self, cmd):
        self.vali.verify_start(cmd)
        quiz_list = []
        self.repo.update("putancur/"+cmd, quiz_list)
        cont = 0
        for question in quiz_list:
            print(f"{question.qid}. {question.text}\na){question.choice_a} b){question.choice_b} c){question.choice_c}")
            while True:
                answer = input("Your answer: ")
                if answer != '':
                    break
            if answer == question.correct_choice:
                    if question.difficulty == 'easy':
                        cont += 1
                    elif question.difficulty == 'hard':
                        cont += 3
                    else:
                        cont += 2
                    print("Correct")
            else:
                print("Incorrect")
        print("Your score: ", cont)


