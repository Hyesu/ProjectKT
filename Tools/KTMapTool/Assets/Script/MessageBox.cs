using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MessageBox : MonoBehaviour
{
    static MessageBox m_instance = null;
    
    public static void Alert(string info)
    {
        m_instance.Show(info);
    }

    GameObject m_ownerObj;
    Text m_infoText;

    void Awake()
    {
        if (m_instance == null)
            m_instance = this;

        m_ownerObj = GameObject.Find("MessageBoxObj");
        m_infoText = GameObject.Find("InfoText").GetComponent<Text>();
        
        m_ownerObj.SetActive(false);
    }

    public void OKBtnClicked()
    {
        m_ownerObj.SetActive(false);
    }

    public void Show(string info)
    {
        m_ownerObj.SetActive(true);
        m_infoText.text = info;
    }
}
