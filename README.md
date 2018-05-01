# produce-consume
C语言实现生产者消费者模型

<p>代码中给了比较详细的注释
</p>

<pre>gcc code.c -o code -lpthread</pre>

<p>结果如下：</p>
<pre>[+] producer produced 4
[-] consumer consumed 4
[+] producer produced 10
[-] consumer consumed 10
[+] producer produced 9
[+] producer produced 5
[-] consumer consumed 5
[+] producer produced 10
[-] consumer consumed 10
[+] producer produced 8
[-] consumer consumed 8
[+] producer produced 10
[+] producer produced 4
[-] consumer consumed 4
[+] producer produced 10
[-] consumer consumed 10
[-] consumer consumed 10
[+] producer produced 2
[-] consumer consumed 2
[+] producer produced 7
[-] consumer consumed 7
[+] producer produced 3
[+] producer produced 5
...</pre>
