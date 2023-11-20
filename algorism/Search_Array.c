int AR_Sequentail_Search(int Arr[], int Target, int len)
{
	int match_idx = -1;

	for (int i = 0; i < len; i++)
		if (Arr[i] == Target)
		{
			match_idx = i;
			break;
		}

	return match_idx;
}

int AR_Move_To_Front(int Arr[], int Target, int len)
{
	int match_idx = -1;
	int temp;

	for (int i = 0; i < len; i++)
	{
		if (Arr[i] == Target)
		{
			match_idx = i;
			
			for (int j = match_idx; j > 0; j--)
			{
				temp = Arr[j];
				Arr[j] = Arr[j - 1];
				Arr[j - 1] = temp;
			}
			break;
		}
	}

	return match_idx;
}

int AR_Transpose(int Arr[], int Target, int len)
{
	int match_idx = -1;
	int temp;

	for (int i = 0; i < len; i++)
	{
		if (Arr[i] == Target)
		{
			match_idx = i;

			temp = Arr[i];
			Arr[i] = Arr[i - 1];
			Arr[i - 1] = temp;
			break;
		}
	}

	return match_idx;
}
