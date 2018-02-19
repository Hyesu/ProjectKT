using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MessageBox : MonoBehaviour
{
    static MessageBox m_instance = null;    
    public static MessageBox GetInstance()
    {
        if(m_instance == null)
            m_instance = GameObject.Find("MessageBox").GetComponent<MessageBox>();

        return m_instance;
    }

    public static void Alert(string info)
    {
        MessageBox.GetInstance().Show(info);
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
