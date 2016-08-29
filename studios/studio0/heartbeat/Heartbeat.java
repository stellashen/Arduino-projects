package studio0.heartbeat;

public class Heartbeat {

	public static void main(String[] args) throws Exception {
		int i = 0;
		while (true){
			i=i+1;
			System.out.println(i+" seconds have elapsed");
			Thread.sleep(1000);
		}

	}

}
