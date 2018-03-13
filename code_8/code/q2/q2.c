int q2(int a1, int a2, int a3) {
	int i = 0;
	switch (a1) {
	case 10: 
		i = a2 + a3;
		break;
	case 12:
		i = a2 - a3;
		break;
	case 14:
		if (a2 > a3)
			i = 0;
		else
			i = 1;
		break;
	case 16:
		if (a3 > a2)
			i = 0;
		else
			i = 1;
		break;
	case 18:
		if (a2 == a3)
			i = 0;
		else
			i = 1;
		break;
	default:
		i = 0;
	}

	return i;
}

int main(void) {
	q2(0, 0, 0);
}