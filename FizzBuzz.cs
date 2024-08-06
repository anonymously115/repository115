using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FizzBuzz : MonoBehaviour
{
    [SerializeField] InputField number;
    [SerializeField] InputField fizz;
    [SerializeField] InputField buzz;
    [SerializeField] Text fizzbuzz;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void OnClick()
    {
        int n = int.Parse(number.text);
        int a = int.Parse(fizz.text);
        int b = int.Parse(buzz.text);
        fizzbuzz.text = "";
        for (int i = 1; i <= n; i++)
        {
            if (i % a == 0 && i % b == 0)
            {
                fizzbuzz.text += "FizzBuzz";
            }
            else if (i % a == 0)
            {
                fizzbuzz.text += "Fizz";
            }
            else if (i % b == 0)
            {
                fizzbuzz.text += "Buzz";
            }
            else
            {
                fizzbuzz.text += i.ToString();
            }
            fizzbuzz.text += "\n";
        }
    }
}
