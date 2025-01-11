package poker

func IsRoyalFlush(cards []*Card) bool {
	if len(cards) < 5 {
		return false
	}

	type royalFlush struct {
		ten   bool
		jack  bool
		queen bool
		king  bool
		ace   bool
	}

	c := make(map[Suite]royalFlush, 4)

	for i := range cards {
		suite := cards[i].Suite

		val, ok := c[suite]
		if !ok {
			val = royalFlush{
				ace:   false,
				king:  false,
				queen: false,
				jack:  false,
				ten:   false,
			}
		}

		switch cards[i].Rank {
		case Ace:
			val.ace = true
		case King:
			val.king = true
		case Queen:
			val.queen = true
		case Jack:
			val.jack = true
		case Ten:
			val.ten = true
		case Eight, Five, Four, Nine, Seven, Six, Three, Two:
			continue
		}

		c[suite] = val

		if c[suite].ten && c[suite].jack && c[suite].queen && c[suite].king && c[suite].ace {
			return true
		}
	}

	return false
}
