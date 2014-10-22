# A python implementation of Affine cipher decoder
# This is a python program I wrote several weeks ago while I was doing my cryptography assignment
# This may help us completing out project

alphabets={};       # Stores the (cipherletter, plainletter) pairs

alphas=[1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25];     # Stores the possible alphas

betas=[];       # Stores the possible betas

ciphertext="yidomxjmeqxjmeqxioiqdyjqvmidvqnmnxjmxjmczsclzmfqxivixsincdcxwdnmzyxqdnixesymflqdseczmqfpmzxmidyxmid";

# Initialize betas
for index in range(0, 26):
	betas.append(index);

# Print all possible plaintexts
for i in range(0, 12):
	for j in range(0, 26):
		print "alhpa =",
		print alphas[i],
		print"\tbeta =",
		print betas[j];
		print "";
                # Calculate the possible cipherletter
		for index in range(97, 123):
			charNum=alphas[i]*(index-97)+betas[j]+97;
			while charNum > 122:
				charNum = charNum - 26;
                                
			alphabets[chr(charNum)]=chr(index);
                # Print the deciphered text
		for n in range(0, len(ciphertext)):
			print alphabets[ciphertext[n]],
		print "\n\n";

