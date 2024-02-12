from Domain.Quiz import quiz


class quiz_repository:
    def __init__(self, filename):
        self.filename = filename
        self.repo = []

    def update(self, filename, repo):
        repo.clear()
        with open(filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if len(line) != 0:
                    parts = line.split(';')
                    Quiz = quiz(parts[0], parts[1], parts[2], parts[3], parts[4], parts[5], parts[6])
                    repo.append(Quiz)

    def list_questions(self, difficulty):
        self.update(self.filename, self.repo)
        list_diff = []
        for element in self.repo:
            if element.difficulty == difficulty:
                list_diff.append(element)

        return list_diff

    def add(self, cmd):
        with open(self.filename, 'a') as f:
            f.write(cmd)
            f.write("\n")

    def check_id(self, qid):
        self.update(self.filename, self.repo)

        for quiz in self.repo:
            if quiz.qid == qid:
                raise
