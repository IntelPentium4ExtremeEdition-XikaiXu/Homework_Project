package poker

type bestResult struct {
	out          []*Card
	combinations int64
	result       Result
}

func BestResult(deck []*Card) (Result, []int64) {
	s := bestResult{
		out:          make([]*Card, 0),
		combinations: 0,
		result:       "",
	}

	s.cardsCombination(deck, 5, 0)

	return s.result, ResultCards(s.result, deck)
}

func (s *bestResult) cardsCombination(deck []*Card, level, i int) {
	if len(deck) == 0 || level > len(deck) {
		return
	}

	if level == 0 {
		s.combinations++
		s.checkCombination(s.out)

		return
	}

	var j int
	for j = i; j < len(deck); j++ {
		s.out = append(s.out, deck[j])
		s.cardsCombination(deck, level-1, j+1)
		s.out = s.out[:len(s.out)-1]

		if (len(s.out) - j) > level {
			return
		}
	}
}

func (s *bestResult) checkCombination(cards []*Card) {
	res := CardsResult(cards)

	if s.result == "" {
		s.result = res
	}

	if s.result.Score() < res.Score() {
		s.result = res
	}
}
