+++++ +++++       intialize counter at cell 0 to 10
[
  >     +++++ ++      add 7 to x at cell 1
  >>    +++++ ++      add 7 to y at cell 3
  <<<   -
]
>               x is at cell 1 with value = 70
>>  [-]         y is at cell 3, with value = 0
Now if we want to assign y = x:

<<   Go back to x at cell 1
.
[
  >> +          increment y at cell 3
  << -
]
>> .
>>
<<<<
>>>> Go to temp at cell 4
[
   <<<< + increment x at cell 0
   >>>> - decrement temp at cell 4
]

<<<< Go back to x

    Print x
    Print y
