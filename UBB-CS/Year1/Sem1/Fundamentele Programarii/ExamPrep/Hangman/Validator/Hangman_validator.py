class validator:
    def check_add(self, sentence):
        if not isinstance(sentence, str):
            raise ValueError
        parts = sentence.split()
        if len(parts) == 0:
            raise ValueError
        for part in parts:
            if len(part) < 3:
                raise ValueError

    def check_letter(self, letter):
        if not isinstance(letter, str):
            raise ValueError
        if len(letter) > 1:
            raise ValueError
