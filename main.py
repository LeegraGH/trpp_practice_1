n=int(input())

ans=[]
for num in range(n+1):
    ans.append(bin(num)[2:].count("1"))

print(ans)
